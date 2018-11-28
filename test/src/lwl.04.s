# qf316
# LWL on 3 byte offset should give 0xF1345678
    .globl entry

entry:
    li $t0, 0x12345678
    li $t1, 0x9ABCDEF1
    li $t2, 0x20000000
    sw $t1, 0($t2)
    lwl $t0, 3($t2)
    srl $t0, 24 # LWL affects MSBs, so shift to RHS to get MSB
    addiu $v0, $t0, 0
    jr $zero
