# ns4516
# SLTI Check -99 is less than 5
    .globl entry

entry:
    li $t0, -99
    slti $v0, $t0, 20
    jr $zero
