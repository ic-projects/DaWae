# ns4516
# LH from uninitialised 0x23FFFFFE
    .globl entry

entry:
    li $t0, 0x23FFFFFE
    lh $v0, 0($t0)
    jr $zero
