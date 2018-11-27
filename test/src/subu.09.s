# ns4516
# SUBU -2147483648 and 2147483647 (should not cause overflow)
    .globl entry

entry:
    li $t1, -2147483648
    li $t2, 2147483647
    subu $v0, $t1, $t2
    jr $zero
