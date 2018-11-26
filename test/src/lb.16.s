# ns4516
# LB 0xFF from 0x20000000 and check sign extended
    .globl entry

entry:
    li $t0, 0x20000000
    li $t1, 0xFF
    sb $t1, 0($t0)
    lb $t2, 0($t0)
    li $t3, 0x30000004
    sw $t2, 0($t3)
    jr $zero
