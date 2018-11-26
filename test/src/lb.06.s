# ns4516
# LB from uninitialised 0x20000000 with 0x4000000 offset causing exception
    .globl entry

entry:
    li $t0, 0x20000000
    lb $v0, 0x4000000($t0)
    jr $zero
