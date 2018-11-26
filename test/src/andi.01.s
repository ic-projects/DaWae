# ns4516
# AND 0xAA against 0s to get 0s
    .globl entry

entry:
    li $t0, 0x0
    andi $v0, $t0, 0xAA
    jr $zero
