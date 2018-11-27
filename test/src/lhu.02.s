# ns4516
# LHU from 0x2000FFFF initalised to be 0xFFAC
    .globl entry

entry:
    li $t0, 0x2000FFFF
    li $t1, 0xFFAC
    sh $t1, 0($t0)
    lhu $v0, 0($t0)
    jr $zero
