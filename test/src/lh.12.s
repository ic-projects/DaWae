# ns4516
# LH from 0x10FFFFFE (exec mem) without exception
    .globl entry

entry:
    li $t0, 0x10FFFFFE
    lh $t1, 0($t0)
    jr $zero
