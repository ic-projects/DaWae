# qf316
# LWR on word aligned memory address should give 0x9ABCDE12
    .globl entry

entry:
    li $t0, 0x12345678
    li $t1, 0x9ABCDEF1
    li $t2, 0x20000000
    sw $t1, 0($t2)
    lwr $t0, 0($t2)
    addiu $v0, $t0, 0
    jr $zero
