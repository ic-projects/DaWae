# ns4516
# Add two large positive integers to cause an overflow
    .globl entry

entry:
    li $t1, 2147483000
    li $t2, 999
    add $v0, $t1, $t2
    jr $zero
