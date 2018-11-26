# ns4516
# LB from 0x20000000 initialised to be 0xFF
    .globl entry

entry:
    li $t0, 0xFF
    li $t1, 0x20000000
    sb $t0, 0($t0)
    lb $v0, 0($t0)
    jr $zero
