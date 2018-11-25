# ns4516
# Add two positive integers
    .globl entry

entry:
    li $t1, 16
    li $t2, 8
    addu $v0, $t1, $t2
    jr $zero
