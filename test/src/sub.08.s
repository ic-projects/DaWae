# ns4516
# SUB 999 and 0
    .globl entry

entry:
    li $t1, 999
    li $t2, 0
    sub $v0, $t1, $t2
    jr $zero
