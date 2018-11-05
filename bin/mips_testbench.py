from subprocess import Popen, PIPE
import os
import time

count = 0
passCount = 0
for test in os.listdir('../test/bin'):
    p = Popen(['./simulator', '../test/bin/' + test], stdout=PIPE, stderr=PIPE, stdin=PIPE)
    while p.poll() is None:
        time.sleep(0.1)
    exitCode = p.returncode

    testName = test.strip('.bin')
    expectedExitCode = open("../test/output/" + testName + ".txt", 'r').readline()

    if (exitCode == expectedExitCode):
        print(str(count) + ': ' + testName + ' - PASS')
        passCount += 1
    else:
        print(str(count) + ': ' + testName + ' - FAIL')

    count += 1

print('Test cases passed: ' + str(passCount) + '/' + str(count) + ' -- ' + str(int(100 * passCount / count)) + '%')
