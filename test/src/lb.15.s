# ns4516
# LB from write only 0x30000004 (memory mapped input)
    .globl entry

entry:
    li $t0, 0x30000004
    lb $v0, 0($t0)
    jr $zero
