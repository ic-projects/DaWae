# ns4516
# SH 0xFFFF in misaligned address 0x20000001
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000001
    sh $t0, 0($t1)
    jr $zero
