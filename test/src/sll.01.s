# Shift left by 3
    .globl entry

entry:
    li $t1, 12
    sll $v0, $t1, 3
    jr $zero