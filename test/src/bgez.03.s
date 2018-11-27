# qf316
# BGEZ on 1 should branch
    .globl entry

entry:
    li $t0, 1
    bgez $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
