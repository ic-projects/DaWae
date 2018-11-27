# ns4516
# SUBU -2147483647 and 1 (should not cause overflow)
    .globl entry

entry:
    li $t1, -2147483647
    li $t2, 1
    subu $v0, $t1, $t2
    jr $zero
