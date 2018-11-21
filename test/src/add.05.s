# Add two large negative integers to cause an overflow
    .globl entry

entry:
    li $t1, -2147483648
    li $t2, -2147483648
    add $v0, $t1, $t2
    jr $zero