# ns4516
# LHU from 0x2000FFFF with offset 0xFFFF initalised to be 0xAC
    .globl entry

entry:
    li $t0, 0x2000FFFF
    li $t1, 0xFFAC
    sh $t1, 0xFFFF($t0)
    lhu $v0, 0xFFFF($t0)
    jr $zero
