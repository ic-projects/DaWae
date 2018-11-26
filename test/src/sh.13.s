# ns4516
# SH to 0x30000000 (mapped input mem) which is read only
    .globl entry

entry:
    li $t0, 0xFFFF
    sh $t0, 0x30000000($zero)
    jr $zero
