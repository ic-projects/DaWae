# ns4516
# Add 100 and 17
    .globl entry

entry:
    li $t1, 100
    li $t2, 17
    add $v0, $t1, $t2
    jr $zero
