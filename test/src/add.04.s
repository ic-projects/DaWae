# Add two negative numbers
    .globl entry

entry:
    li $t1, -16
    li $t2, -16
    add $v0, $t1, $t2
    jr $zero