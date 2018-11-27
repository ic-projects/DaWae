# ns4516
# SLTI Check 0 is not less than 0
    .globl entry

entry:
    slti $v0, $t0, 0
    jr $zero
