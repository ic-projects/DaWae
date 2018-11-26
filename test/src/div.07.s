# ns4516
# DIV -100 by 12 checking quotient
    .globl entry

entry:
    li $t0, -100
    li $t1, 12
    div $t0, $t1
    mflo $v0
    jr $zero
