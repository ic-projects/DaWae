# ns4516
# SB 0xF in 0x20000000(min addr) without exception
    .globl entry

entry:
    li $t0, 0xF
    li $t1, 0x20000000
    sb $t0, 0($t1)
    jr $zero
