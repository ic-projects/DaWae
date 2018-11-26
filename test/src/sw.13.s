# ns4516
# SW 0xFFFFFFFF in misaligned address 0x20000003
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000003
    sw $t0, 0($t1)
    jr $zero
