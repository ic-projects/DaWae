# ns4516
# OR 0xFFFFFFFF and 0x00AA0020 to get 1s
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x00AA0020
    or $v0, $t0, $t1
    jr $zero
