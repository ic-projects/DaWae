# ns4516
# SUB 0 and -5
    .globl entry

entry:
    li $t1, 0
    li $t2, -5
    sub $v0, $t1, $t2
    jr $zero
