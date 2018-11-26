# ns4516
# LW from 0x20000000 initialised to be 0xFFFFFFFF
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000000
    sw $t0, 0($t1)
    lw $v0, 0($t1)
    jr $zero
