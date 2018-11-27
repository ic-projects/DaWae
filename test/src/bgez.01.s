# qf316
# BGEZ on -16 should not branch
    .globl entry

entry:
    li $t0, -16
    bgez $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
