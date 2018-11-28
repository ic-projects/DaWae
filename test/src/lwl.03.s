# qf316
# LWL on half-word offset should give 0xDEF15678
    .globl entry

entry:
    li $t0, 0x12345678
    li $t1, 0x9ABCDEF1
    li $t2, 0x20000000
    sw $t1, 0($t2)
    lwl $t0, 2($t2)
    srl $t0, 16 # LWL affects MSBs, so shift to RHS to get 3rd byte
    addiu $v0, $t0, 0
    jr $zero
