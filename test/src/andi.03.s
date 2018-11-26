# ns4516
# ANDI 0x00AC against 0xB0D0
    .globl entry

entry:
    li $t1, 0x00AC
    andi $v0, $t1, 0xB0D0
    jr $zero
