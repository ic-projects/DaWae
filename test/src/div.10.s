# ns4516
# DIV -999 by 0 causing exception
    .globl entry

entry:
    li $t0, -999
    li $t1, 0
    div $t0, $t1
    mfhi $v0
    jr $zero
