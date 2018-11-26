# ns4516
# Add 1 to 2147483647 in $v0 (should cause overflow)
    .globl entry

entry:
    li $v0, 2147483647
    addi $v0, $v0, 1
    jr $zero
