# ns4516
# XOR 0xFFFFFFFF and 0x00AA0020
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    xor $v0, $t0, 0x00AA0020
    jr $zero
