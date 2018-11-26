# ns4516
# LW from misaligned memory address 0x20000002
    .globl entry

entry:
    li $t0, 0x20000002
    lw $v0, 0($t0)
    jr $zero
