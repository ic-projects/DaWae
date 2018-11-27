# ns4516
# LBU from invalid memory address 0x1FFFFFFF
    .globl entry

entry:
    li $t0, 0x1FFFFFFF
    lbu $v0, 0($t0)
    jr $zero
