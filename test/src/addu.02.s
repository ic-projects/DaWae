# qf316
# Add two large positive integers without overflow
    .globl entry

entry:
    li $t1, 2147483000
    li $t2, 99999999
    addu $v0, $t1, $t2
    jr $zero
