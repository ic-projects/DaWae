# ns4516
# SLTU Check 0 is not less than 0
    .globl entry

entry:
    sltu $v0, $t0, $t1
    jr $zero
