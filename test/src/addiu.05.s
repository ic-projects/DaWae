# ns4516
# Add -10 to -2147483648 in $v0 (should cause overflow without exception)
    .globl entry

entry:
    li $v0, -2147483648
    addi $v0, $v0, -10
    jr $zero
