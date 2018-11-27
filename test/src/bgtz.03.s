# qf316
# BGTZ on 1 should branch
    .globl entry

entry:
    li $t0, 1
    bgtz $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
