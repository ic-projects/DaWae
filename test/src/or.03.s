# ns4516
# OR 0x00AC against 0xB0D0
    .globl entry

entry:
    li $t1, 0x00AC
    li $t2, 0xB0D0
    or $v0, $t1, $t2
    jr $zero
