# ns4516
# LH from uninitialised 0x1FFFFFFF causing exception
    .globl entry

entry:
    li $t0, 0x1FFFFFFF
    lh $v0, 0($t0)
    jr $zero
