# ns4516
# LB from 0x20000000 with offset 0x10000 initialised to be 0xFF
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000000
    sw $t0, 0x10000($t1)
    lb $v0, 0x10000($t1)
    jr $zero
