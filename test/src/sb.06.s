# ns4516
# SB 0xFF in 0x20000000 with 0x4000000 offset with exception
    .globl entry

entry:
    li $t0, 0xFF
    li $t1, 0x20000000
    sb $t0, 0x4000000($t1)
    jr $zero
