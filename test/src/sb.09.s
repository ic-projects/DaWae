# ns4516
# SB uninitialised reg in 0x20000000
    .globl entry

entry:
    li $t1, 0x20000000
    sb $t0, 0($t1)
    jr $zero
