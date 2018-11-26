# ns4516
# LH from uninitialised 0x23FFFFFF causing exception
    .globl entry

entry:
    li $t0, 0x23FFFFFF
    lh $v0, 0($t0)
    jr $zero
