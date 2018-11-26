# ns4516
# SH 0xFFFF in misaligned address 0x20000000 with offset 0x3FF
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000000
    sh $t0, 0x3FF($t1)
    jr $zero
