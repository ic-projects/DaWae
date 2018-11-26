# ns4516
# LB from 0x10FFFFFF (exec mem) without exception
    .globl entry

entry:
    li $t0, 0x10FFFFFF
    lb $t1, 0($t0)
    jr $zero
