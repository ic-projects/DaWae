# ns4516
# SH uninitialised reg in 0x20000000
    .globl entry

entry:
    li $t1, 0x20000000
    sh $t0, 0($t1)
    jr $zero
