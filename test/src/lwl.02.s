# qf316
# LWL on 1 byte word offset should put give 0xBCDEF178
    .globl entry

entry:
    li $t0, 0x12345678
    li $t1, 0x9ABCDEF1
    li $t2, 0x20000000
    sw $t1, 0($t2)
    lwl $t0, 1($t2)
    addiu $v0, $t0, 0
    jr $zero
