# ns4516
# MULT 999 by 0 checking LO
    .globl entry

entry:
    li $t0, 999
    li $t1, 0
    mult $t0, $t1
    mflo $v0
    jr $zero
