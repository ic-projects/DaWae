# ns4516
# LB from 0xFFFFFFF (1 below exec mem) causing exception
    .globl entry

entry:
    li $t0, 0xFFFFFFF
    lb $v0, 0($t0)
    jr $zero
