# ns4516
# SB 0xFF in 0x200000FF with -255 offset without exception
    .globl entry

entry:
    li $t0, 0xFF
    li $t1, -255
    sb $t0, 0x200000FF($t1)
    jr $zero
