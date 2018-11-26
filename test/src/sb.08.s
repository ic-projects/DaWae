# ns4516
# SB 0xFF in 0x200000FF with -256 offset with exception
    .globl entry

entry:
    li $t0, 0xFF
    li $t1, 0x20000000
    sb $t0, -256($t1)
    jr $zero
