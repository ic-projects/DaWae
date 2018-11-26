# ns4516
# OR 0xFFFFFFFF and 0x00AA0020 to get itself
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    andi $v0, $t0, 0x00AA0020
    jr $zero
