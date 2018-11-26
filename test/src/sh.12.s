# ns4516
# SH to 0x10000000 (exec mem) which is read only
    .globl entry

entry:
    li $t0, 0xFFFF
    sh $t0, 0x10000000($zero)
    jr $zero
