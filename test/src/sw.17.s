# ns4516
# SW to 0x30000000 (mapped input mem) which is read only
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    sw $t0, 0x30000000($zero)
    jr $zero
