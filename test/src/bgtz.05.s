# qf316
# BGTZ on 0 should not branch
    .globl entry

entry:
    bgtz $t0, exit
    add $v0, $zero, 50

exit:
    jr $zero
