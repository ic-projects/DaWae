# ns4516
# MULT 1299100821 by 91298749 checking LO
    .globl entry

entry:
    li $t0, 1299100821
    li $t1, 91298749
    mult $t0, $t1
    mflo $v0
    jr $zero
