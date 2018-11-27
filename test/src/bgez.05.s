# qf316
# BGEZ on 0 should branch
    .globl entry

entry:
    bgez $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
