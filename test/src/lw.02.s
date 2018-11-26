# ns4516
# LW from uninitialised 0x1FFFFFFF causing exception
    .globl entry

entry:
    li $t0, 0x1FFFFFFC
    lw $v0, 0($t0)
    jr $zero
