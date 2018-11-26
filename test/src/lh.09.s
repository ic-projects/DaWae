# ns4516
# LH from 0x20000000 initialised to be 0xFFFF
    .globl entry

entry:
    li $t0, 0xFFFF
    li $t1, 0x20000000
    sh $t0, 0($t1)
    lh $v0, 0($t1)
    jr $zero
