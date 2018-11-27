# qf316
# JALR should store return address in specified register
    .globl entry
    .set noreorder

entry:
    li $t0, 0x10000000
    bne $t1, $zero, exit
    jalr $t1, $t0
    nop
    add $v0, $zero, 69

exit:
    jr $zero
