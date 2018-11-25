# ns4516
# Add a negative number
    .globl entry

entry:
    li $t1, 0
    li $t2, -5
    add $v0, $t1, $t2
    jr $zero
