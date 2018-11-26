# ns4516
# LB from uninitialised 0x24000000 causing exception
    .globl entry

entry:
    li $t0, 0x24000000
    lb $v0, 0($t0)
    jr $zero
