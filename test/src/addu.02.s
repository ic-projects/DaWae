# qf316
# Add 2147483000 and 99999999 (should overflow without exception)
    .globl entry

entry:
    li $t1, 2147483000
    li $t2, 99999999
    addu $v0, $t1, $t2
    jr $zero
