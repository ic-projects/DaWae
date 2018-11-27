# qf316
# BLTZ on 0 should not branch
    .globl entry

entry:
    bltz $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
