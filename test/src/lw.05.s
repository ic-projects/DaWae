# ns4516
# LW from uninitialised 0x20000000 with 0x3FFFFFC offset
    .globl entry

entry:
    li $t0, 0x20000000
    lw $v0, 0x3FFFFFC($t0)
    jr $zero
