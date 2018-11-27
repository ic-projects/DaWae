# qf316
# Unconditional jump to exit should exit immediately
    .globl entry

entry:
    li $t0, 69
    j exit
    add $v0, $zero, $t0

exit:
    jr $zero
