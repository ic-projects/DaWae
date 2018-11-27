# ns4516
# XORI 0xAA against 0s to get itself
    .globl entry

entry:
    xori $v0, $t0, 0xAA
    jr $zero
