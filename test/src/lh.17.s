# ns4516
# LH from misaligned memory address 0x20000000 with offset 0xFF
    .globl entry

entry:
    li $t0, 0x20000000
    lh $v0, 0xFF($t0)
    jr $zero
