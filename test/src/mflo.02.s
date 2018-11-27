# ns4516
# Load 100 into LO with 200 / 2 and retrieve
    .globl entry

entry:
    li $t0, 200
    li $t1, 2
    div $t0, $t1
    mflo $v0
    jr $zero
