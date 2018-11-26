# ns4516
# SW 0xFFFFFFFF in 0x20000000 with 0x3FFFFFD offset with exception
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000000
    sw $t0, 0x3FFFFFD($t1)
    jr $zero
