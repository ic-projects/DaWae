# ns4516
# LBU from invalid memory address 0x24000000
    .globl entry

entry:
    li $t0, 0x24000000
    lbu $v0, 0($t0)
    jr $zero
