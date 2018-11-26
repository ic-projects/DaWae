# ns4516
# SW 0xFFFFFFFF in 0x200000FF with -256 offset with exception
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000000
    sw $t0, -256($t1)
    jr $zero
