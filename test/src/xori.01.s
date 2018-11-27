# ns4516
# XOR 0xAA against 0s to get itself
    .globl entry

entry:
    xor $v0, $t0, 0xAA
    jr $zero
