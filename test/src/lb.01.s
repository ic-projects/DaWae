# ns4516
# LB from uninitialised 0x20000000
    .globl entry

entry:
    li $t0, 0x20000000
    lb $v0, 0($t0)
    jr $zero
