# ns4516
# LBU from 0x2000FFFF initalised to be 0xAC
    .globl entry

entry:
    li $t0, 0x2000FFFF
    li $t1, 0xAC
    sb $t1, 0($t0)
    lbu $v0, 0($t0)
    jr $zero
