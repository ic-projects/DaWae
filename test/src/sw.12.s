# ns4516
# SW 0xFFFFFFFF in misaligned address 0x20000002
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000002
    sw $t0, 0($t1)
    jr $zero
