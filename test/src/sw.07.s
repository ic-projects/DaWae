# ns4516
# SW 0xFFFFFFFF in 0x200000FF with -255 offset without exception
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x200000FF
    sw $t0, -255($t1)
    jr $zero
