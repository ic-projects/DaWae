# qf316
# BLEZ on 0 should branch
    .globl entry

entry:
    blez $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
