# Add two positive integers
    .globl entry

entry:
    li $t1, 100
    li $t2, 17
    add $v0, $t1, $t2
    jr $zero