# ns4516
# LW from 0xFFFFFFF (1 below exec mem) causing exception
    .globl entry

entry:
    li $t0, 0xFFFFFFF
    lw $v0, 0($t0)
    jr $zero
