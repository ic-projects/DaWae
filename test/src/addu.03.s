# ns4516
# Add -2147483648 and -1 (should overflow without exception)
    .globl entry

entry:
    li $t1, -2147483648
    li $t2, -1
    addu $v0, $t1, $t2
    jr $zero
