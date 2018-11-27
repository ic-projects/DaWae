# ns4516
# MULT max int by max int checking HI
    .globl entry

entry:
    li $t0, 2147483647
    li $t1, 2147483647
    mult $t0, $t1
    mfhi $v0
    jr $zero
