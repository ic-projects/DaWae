# ns4516
# DIVU 24 by 3 checking quotient
    .globl entry

entry:
    li $t0, 24
    li $t1, 3
    divu $t0, $t1
    mflo $v0
    jr $zero
