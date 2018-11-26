# ns4516
# SH 0xFFFF in 0x20000000 with 0x3FFFFFF offset with exception
    .globl entry

entry:
    li $t0, 0xFFFF
    li $t1, 0x20000000
    sh $t0, 0x3FFFFFF($t1)
    jr $zero
