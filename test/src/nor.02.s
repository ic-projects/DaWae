# NOR two 0s
    .globl entry

entry:
    li $t1, 0x0
    li $t2, 0x0
    nor $v0, $t1, $t2
    jr $zero