# ns4516
# SW 0xFFFFFFFF in 0x23FFFFFC(max addr) without exception
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    sw $t0, 0x23FFFFFC($zero)
    jr $zero
