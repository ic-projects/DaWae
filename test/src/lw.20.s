# ns4516
# LW from misaligned memory address 0x20000000 with offset 0xFE
    .globl entry

entry:
    li $t0, 0x20000000
    lw $v0, 0xFE($t0)
    jr $zero
