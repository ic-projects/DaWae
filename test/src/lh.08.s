# ns4516
# LH from uninitialised 0x200000FF with -256 offset causing exception
    .globl entry

entry:
    li $t0, 0x200000FF
    lh $v0, -256($t0)
    jr $zero
