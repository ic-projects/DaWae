# ns4516
# MULT register holding 10 against itself checking HI
    .globl entry

entry:
    li $t0, 10
    mult $t0, $t0
    mfhi $v0
    jr $zero
