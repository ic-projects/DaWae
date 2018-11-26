# ns4516
# SH 0xFFFF in 0x20000000(min addr) without exception
    .globl entry

entry:
    li $t0, 0xFFFF
    li $t1, 0x20000000
    sh $t0, 0($t1)
    jr $zero
