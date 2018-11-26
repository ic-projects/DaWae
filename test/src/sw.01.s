# ns4516
# SW 0xFFFFFFFF in 0x20000000(min addr) without exception
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000000
    sw $t0, 0($t1)
    jr $zero
