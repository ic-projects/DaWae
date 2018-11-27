# ns4516
# SUB 100 and 17
    .globl entry

entry:
    li $t1, 100
    li $t2, 17
    sub $v0, $t1, $t2
    jr $zero
