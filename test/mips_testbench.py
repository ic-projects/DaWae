from subprocess import Popen, PIPE
import os
import time

count = 0
passCount = 0
for test in os.listdir('bin'):
    p = Popen(['../bin/mips_simulator', 'bin/' + test], stdout=PIPE, stderr=PIPE, stdin=PIPE)
    while p.poll() is None:
        time.sleep(0.1)
    exitCode = p.returncode

    testName = test.strip('.bin')
    expectedExitCode = int(open('output/' + testName + '.txt', 'r').readline())

    # Checking exit code
    if exitCode == expectedExitCode:
        print('{}: {} - PASS'.format(count, testName))
        passCount += 1
    else:
        print('{}: {} - FAIL (expected: {}, received: {})'.format(count, testName, expectedExitCode, exitCode))

    # Checking std::out

    count += 1

print('Test cases passed: {}/{} -- {}%'.format(passCount, count, 100 * passCount / count))
