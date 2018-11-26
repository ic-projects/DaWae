# ns4516
# SB 0xF in 0x20000000 with 0x3FFFFFF base without exception
    .globl entry

entry:
    li $t0, 0xF
    li $t1, 0x3FFFFFF
    sb $t0, 0x20000000($t1)
    jr $zero
