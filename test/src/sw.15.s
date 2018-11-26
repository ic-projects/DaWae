# ns4516
# SW 0xFFFFFFFF in misaligned address 0x20000000 with offset 0x7D3
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x20000000
    sw $t0, 0x7D3($t1)
    jr $zero
