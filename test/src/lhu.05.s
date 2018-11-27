# ns4516
# LHU from invalid memory address 0x1FFFFFFF
    .globl entry

entry:
    li $t0, 0x1FFFFFFF
    lhu $v0, 0($t0)
    jr $zero
