# ns4516
# LW from 0x10000000 (exec mem) without exception
    .globl entry

entry:
    li $t0, 0x10000000
    lw $t1, 0($t0)
    jr $zero
