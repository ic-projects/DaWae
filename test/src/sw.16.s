# ns4516
# SW to 0x10000000 (exec mem) which is read only
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    sw $t0, 0x10000000($zero)
    jr $zero
