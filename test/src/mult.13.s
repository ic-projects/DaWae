# ns4516
# MULT -8 by 9 checking LO
    .globl entry

entry:
    li $t0, -8
    li $t1, 9
    mult $t0, $t1
    mflo $v0
    jr $zero
