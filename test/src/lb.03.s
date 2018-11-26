# ns4516
# LB from uninitialised 0x23FFFFFF
    .globl entry

entry:
    li $t0, 0x23FFFFFF
    lb $v0, 0($t0)
    jr $zero
