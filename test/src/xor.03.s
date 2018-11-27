# ns4516
# XOR 0x00AC against 0xB0D0
    .globl entry

entry:
    li $t1, 0x00AC
    li $t2, 0xB0D0
    xor $v0, $t1, $t2
    jr $zero
