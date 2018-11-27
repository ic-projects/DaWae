from subprocess import Popen, PIPE
import os
import sys

# Compile assembly test files into binary
os.system('mkdir -p test/bin')
for test in os.listdir('test/src'):
    testName = test[:-2]
    os.system('make test/bin/{}.mips.bin > /dev/null'.format(testName))

count = 0
passCount = 0
for test in sorted(os.listdir('test/bin')):
    p = Popen([sys.argv[1], 'test/bin/' + test], stdout=PIPE, stderr=PIPE, stdin=PIPE)
    while p.poll() is None:
        continue
    exitCode = int(p.returncode)
    output, err = p.communicate()

    # Output any errors received
    if err:
        sys.stderr.write(err)
        continue

    output = output.rstrip('\0')

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
        print('{}, {}, Pass, {}, {}'.format(testName, instruction, author, description))
        passCount += 1
    else:
        print('{}, {}, Fail, {}, {}'.format(testName, instruction, author, description))
        # Print error message with red text
        sys.stderr.write('ERROR: Exit code was {} and expected {}; Output was "{}" and expected "{}"\n'.format(exitCode, expectedExitCode, output, expectedOut))

    count += 1

print('Test cases passed: {}/{} -- {}%'.format(passCount, count, 100 * passCount / count))
