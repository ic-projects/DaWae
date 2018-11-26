# ns4516
# Add 1 to 2147483646 in $v0 (should not cause overflow)
    .globl entry

entry:
    li $v0, 2147483646
    addiu $v0, $v0, 1
    jr $zero
