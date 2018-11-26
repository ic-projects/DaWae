# ns4516
# LW from 0x10FFFFFC (exec mem) without exception
    .globl entry

entry:
    li $t0, 0x10FFFFFC
    lw $t1, 0($t0)
    jr $zero
