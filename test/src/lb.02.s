# ns4516
# LB from uninitialised 0x1FFFFFFF causing exception
    .globl entry

entry:
    li $t0, 0x1FFFFFFF
    lb $v0, 0($t0)
    jr $zero
