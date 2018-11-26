# ns4516
# SW uninitialised reg in 0x20000000
    .globl entry

entry:
    li $t1, 0x20000000
    sw $t0, 0($t1)
    jr $zero
