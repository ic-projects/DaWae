# ns4516
# DIV 100 by 12 checking remainder
    .globl entry

entry:
    li $t0, 100
    li $t1, 12
    div $t0, $t1
    mfhi $v0
    jr $zero
