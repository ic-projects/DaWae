# qf316
# ORI 0xAA against 0s to get itself
    .globl entry

entry:
    li $t0, 0x0
    ori $v0, $t0, 0xAA
    jr $zero
