# ns4516
# Add 2147483000 and 999 (should cause overflow)
    .globl entry

entry:
    li $t1, 2147483000
    li $t2, 999
    add $v0, $t1, $t2
    jr $zero
