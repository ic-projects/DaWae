# ns4516
# MULT register holding 10 against itself checking LO
    .globl entry

entry:
    li $t0, 10
    mult $t0, $t0
    mflo $v0
    jr $zero
