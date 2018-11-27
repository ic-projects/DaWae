# qf316
# JR only after executing instruction in branch delay slot
    .globl entry
    .set noreorder

entry:
    li $t0, 0x10000000
    li $t2, 5
    beq $t1, $t2, exit
    add $t1, $t1, 1
    jr $t0
    add $t3, $t3, 2

exit:
    add $v0, $t3, 0
    jr $zero
