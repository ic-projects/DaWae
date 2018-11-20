from subprocess import Popen, PIPE
import os
import time

# Compile assembly test files into binary
os.system('mkdir bin')
for test in os.listdir('src'):
    testName = test.strip('.s')
    os.system('make test/bin/{}.mips.bin -C ../'.format(testName))

count = 0
passCount = 0
for test in os.listdir('bin'):
    p = Popen(['../bin/mips_simulator', 'bin/' + test], stdout=PIPE, stderr=PIPE, stdin=PIPE)
    while p.poll() is None:
        time.sleep(0.1)
    exitCode = p.returncode
    output = p.communicate()[0].rstrip('\0')

    # Remove .mips.bin file ending
    testName = test[:-9]

    with open('./output/' + testName + '.mips.out', 'r') as f:
        #Mod exit code by 256 since exit code size is only 8 bits
        expectedExitCode = int(f.readline()) % 256
        expectedOut = f.readline()

    # Get test description
    descComment = open('./src/{}.s'.format(testName), 'r').readline()
    comment = descComment.strip('# \n')

    print('{}: {} - {} '.format(count, testName, comment))

    exitCodePass = False
    outputPass = False
    # Checking exit code
    if exitCode == expectedExitCode:
        print('Exit Code - PASS')
        exitCodePass = True
    else:
        print('Exit Code - FAIL (expected: {}, received: {})'.format(expectedExitCode, exitCode))

    # Checking std::out
    if output == expectedOut:
        print('Output    - PASS')
        outputPass = True
    else:
        print('Output - FAIL (expected: {}, received: {})'.format(expectedOut, output))

    if exitCodePass and outputPass:
        passCount += 1

    count += 1

print('Test cases passed: {}/{} -- {}%'.format(passCount, count, 100 * passCount / count))
