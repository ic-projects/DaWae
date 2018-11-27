# ns4516
# SLTI Check 20 is not less than 5
    .globl entry

entry:
    li $t0, 20
    slti $v0, $t0, 5
    jr $zero
