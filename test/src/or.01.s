# qf316
# OR a number against 0s to get 0s
    .globl entry

entry:
    li $t0, 0x0
    li $t1, 0xAA
    or $v0, $t0, $t1
    jr $zero
