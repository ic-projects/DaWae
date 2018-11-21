# NOR mix of 0s and 1s
    .globl entry

entry:
    li $t1, 0xA0C
    li $t2, 0x2020
    nor $v0, $t1, $t2
    jr $zero