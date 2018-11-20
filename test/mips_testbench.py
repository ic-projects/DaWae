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
    output = p.communicate()[0]

    testName = test.strip('.bin')

    with open('./output/' + testName + '.out', 'r') as f:
        expectedExitCode = int(f.readline())
        expectedOut = f.readline()

    exitCodePass = False
    outputPass = False

    # Checking exit code
    if exitCode == expectedExitCode:
        print('{}: {} - Exit Code - PASS'.format(count, testName))
        exitCodePass = True
    else:
        print('{}: {} - Exit Code - FAIL (expected: {}, received: {})'.format(count, testName, expectedExitCode, exitCode))

    # Checking std::out
    if output == expectedOut:
        print('{}: {} - Output    - PASS'.format(count, testName))
        outputPass = True
    else:
        print('{}: {} - Output - FAIL (expected: {}, received: {})'.format(count, testName, expectedOut, output))

    if exitCodePass and outputPass:
        passCount += 1

    count += 1

print('Test cases passed: {}/{} -- {}%'.format(passCount, count, 100 * passCount / count))
