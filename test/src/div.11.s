# ns4516
# DIV 0 by 0 causing exception
    .globl entry

entry:
    li $t0, 0
    li $t1, 0
    div $t0, $t1
    mfhi $v0
    jr $zero
