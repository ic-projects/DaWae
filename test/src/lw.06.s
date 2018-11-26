# ns4516
# LW from uninitialised 0x20000000 with 0x3FFFFFD offset causing exception
    .globl entry

entry:
    li $t0, 0x20000000
    lw $v0, 0x3FFFFFD($t0)
    jr $zero
