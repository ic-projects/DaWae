# ns4516
# AND 0xFFFFFFFF and 0x00AA0020 to get itself
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x00AA0020
    and $v0, $t0, $t1
    jr $zero
