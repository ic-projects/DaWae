# ns4516
# LBU from 0x2000FFFF with offset 0xFFFF initalised to be 0xAC
    .globl entry

entry:
    li $t0, 0x2000FFFF
    li $t1, 0xAC
    sb $t1, 0xFFFF($t0)
    lbu $v0, 0xFFFF($t0)
    jr $zero
