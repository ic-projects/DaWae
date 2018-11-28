from subprocess import Popen, PIPE
from threading import Timer
import os
import sys

TEST_TIMEOUT = 5

# Compile assembly test files into binary
os.system('mkdir -p test/bin')
for test in os.listdir('test/src'):
    testName = test[:-2]
    os.system('make test/bin/{}.mips.bin > /dev/null'.format(testName))

count = 0
passCount = 0
for test in sorted(os.listdir('test/bin')):
    # Remove .mips.bin file ending
    testName = test[:-9]

    input = PIPE
    # Check if input files exist
    if os.path.isfile('test/input/{}.in'.format(testName)):
        input = open('test/input/{}.in'.format(testName))

    p = Popen([sys.argv[1], 'test/bin/' + test], stdout=PIPE, stderr=PIPE, stdin=input)

    # Kill simulator if test takes longer than TEST_TIMEOUT seconds
    timer = Timer(TEST_TIMEOUT, p.kill)
    timer.start()

    output, err = p.communicate()
    exitCode = int(p.returncode)

    # Output any errors received
    if err:
        sys.stderr.write(err)

    output = output.rstrip('\0')

    with open('test/output/' + testName + '.mips.out', 'r') as f:
        # Exit code modulo 256 since exit code size is only 8 bits
        expectedExitCode = int(f.readline()) % 256
        expectedOut = f.read()

    # Get test author and description
    testFile = None
    if os.path.isfile('test/src/{}.s'.format(testName)):
        testFile = open('test/src/{}.s'.format(testName), 'r')
    elif os.path.isfile('test/src/{}.c'.format(testName)):
        testFile = open('test/src/{}.c'.format(testName), 'r')
    else:
        continue

    author = testFile.readline().strip('#\n/, ')
    description = testFile.readline().strip('#\n/, ')
    instruction = testName.split('.')[0].upper()

    if exitCode == expectedExitCode and output == expectedOut:
        print('{}, {}, Pass, {}, {}'.format(testName, instruction, author, description))
        passCount += 1
    else:
        print('{}, {}, Fail, {}, {}'.format(testName, instruction, author, description))
        # Print error message with red text
        sys.stderr.write('ERROR FROM {}: Exit code was {} and expected {}; Output was "{}" and expected "{}"\n'.format(testName, exitCode, expectedExitCode, output, expectedOut))

    timer.cancel()
    count += 1

sys.stderr.write('Test cases passed: {}/{} -- {}%\n'.format(passCount, count, 100 * passCount / count))
