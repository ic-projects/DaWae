# ns4516
# XOR 0xFFFFFFFF and 0x00AA0020
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x00AA0020
    xor $v0, $t0, $t1
    jr $zero
