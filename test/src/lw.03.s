# ns4516
# LW from uninitialised 0x23FFFFFC
    .globl entry

entry:
    li $t0, 0x23FFFFFC
    lw $v0, 0($t0)
    jr $zero
