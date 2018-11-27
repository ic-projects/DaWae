# ns4516
# Load 100 into HI with 100 / 101 and retrieve
    .globl entry

entry:
    li $t0, 100
    li $t1, 101
    div $t0, $t1
    mfhi $v0
    jr $zero
