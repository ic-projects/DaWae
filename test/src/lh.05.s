# ns4516
# LH from uninitialised 0x20000000 with 0x3FFFFFE offset
    .globl entry

entry:
    li $t0, 0x20000000
    lh $v0, 0x3FFFFFE($t0)
    jr $zero
