# ns4516
# LH from write only 0x30000004 (memory mapped input)
    .globl entry

entry:
    li $t0, 0x30000004
    lh $v0, 0($t0)
    jr $zero
