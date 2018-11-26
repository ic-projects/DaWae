# ns4516
# SW 0xFFFFFFFF in misaligned address 0x20000000 with offset 0x3FF
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000000
    sw $t0, 0x3FF($t1)
    jr $zero
