# ns4516
# XOR 0xAA against 0s to get itself
    .globl entry

entry:
    li $t0, 0x0
    li $t1, 0xAA
    xor $v0, $t0, $t1
    jr $zero
