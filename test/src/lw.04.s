# ns4516
# LW from uninitialised 0x23FFFFFD causing exception
    .globl entry

entry:
    li $t0, 0x23FFFFFD
    lw $v0, 0($t0)
    jr $zero
