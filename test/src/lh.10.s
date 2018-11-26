# ns4516
# LH from 0x20000000 with offset 0x10000 initialised to be 0xFFFF
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000000
    sw $t0, 0x10000($t1)
    lh $v0, 0x10000($t1)
    jr $zero
