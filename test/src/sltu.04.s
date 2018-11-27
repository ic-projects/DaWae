# ns4516
# SLTU Check -99 isn't less than 5
    .globl entry

entry:
    li $t0, -99
    li $t1, 20
    sltu $v0, $t0, $t1
    jr $zero
