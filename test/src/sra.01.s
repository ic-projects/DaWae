# qf316
# Shift right arithmetic -1000 by 3 should give -125
    .globl entry

entry:
    li $t1, -1000
    sra $v0, $t1, 3
    jr $zero
