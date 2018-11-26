# ns4516
# LB from 0x11000000 (1 above exec mem) causing exception
    .globl entry

entry:
    li $t0, 0x11000000
    lb $v0, 0($t0)
    jr $zero
