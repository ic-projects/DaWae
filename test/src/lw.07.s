# ns4516
# LW from uninitialised 0x200000FF with -255 offset
    .globl entry

entry:
    li $t0, 0x200000FF
    lw $v0, -255($t0)
    jr $zero
