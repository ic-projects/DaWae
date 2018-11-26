# ns4516
# ANDI 0xFFFFFFFF and 0x29FC to get itself
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    andi $v0, $t0, 0x29FC
    jr $zero
