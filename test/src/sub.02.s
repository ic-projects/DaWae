# ns4516
# SUB -2147483648 and 1 (should cause overflow)
    .globl entry

entry:
    li $t1, -2147483648
    li $t2, 1
    sub $v0, $t1, $t2
    jr $zero
