# qf316
# BGTZ on 2147483647 (MAX_INT) should branch
    .globl entry

entry:
    li $t0, 2147483647
    bgtz $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
