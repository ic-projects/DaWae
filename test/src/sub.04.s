# qf316
# SUB -16 and -16
    .globl entry

entry:
    li $t1, -16
    li $t2, -16
    sub $v0, $t1, $t2
    jr $zero
