# ns4516
# LHU from unaligned memory address 0x20000001
    .globl entry

entry:
    li $t0, 0x20000001
    lhu $v0, 0($t0)
    jr $zero
