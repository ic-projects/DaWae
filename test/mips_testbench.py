from subprocess import Popen, PIPE
import os
import time
import sys

# Compile assembly test files into binary
os.system('mkdir -p test/bin')
for test in os.listdir('test/src'):
    testName = test[:-2]
    os.system('make test/bin/{}.mips.bin > /dev/null'.format(testName))

count = 0
passCount = 0
for test in os.listdir('test/bin'):
    p = Popen([sys.argv[1], 'test/bin/' + test], stdout=PIPE, stderr=PIPE, stdin=PIPE)
    while p.poll() is None:
        time.sleep(0.1)
    exitCode = p.returncode
    output = p.communicate()[0].rstrip('\0')

    # Remove .mips.bin file ending
    testName = test[:-9]

    with open('test/output/' + testName + '.mips.out', 'r') as f:
        # Exit code modulo 256 since exit code size is only 8 bits
        expectedExitCode = int(f.readline()) % 256
        expectedOut = f.read()

    # Get test author and description
    testFile = open('test/src/{}.s'.format(testName), 'r')
    author = testFile.readline().strip('# \n')
    description = testFile.readline().strip('# \n')
    instruction = testName.split('.')[0].upper()

    if exitCode == expectedExitCode and output == expectedOut:
        print('{:10} {:7} Pass, {:7} {:1}'.format(testName + ',', instruction + ',', author + ',', description))
        passCount += 1
    else:
        print('{:10} {:7} Fail, {:7} {:1}'.format(testName + ',', instruction + ',', author + ',', description))
        # Print error message with red text
        sys.stderr.write('\033[91mExited with {} and expected {}; Output was "{}" and expected "{}"\033[0m\n'.format(exitCode, expectedExitCode, output, expectedOut))

    count += 1

print('Test cases passed: {}/{} -- {}%'.format(passCount, count, 100 * passCount / count))
