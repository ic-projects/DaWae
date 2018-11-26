# ns4516
# Add -1 to -2147483647 (should not cause overflow)
    .globl entry

entry:
    li $t1, -1
    li $t2, -2147483647
    add $v0, $t1, $t2
    jr $zero
