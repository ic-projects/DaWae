# ns4516
# XORI 0xFFFFFFFF and 0xAA20
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    xori $v0, $t0, 0xAA20
    jr $zero
