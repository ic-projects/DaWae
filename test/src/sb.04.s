# ns4516
# SB 0xF in 0x24000000 with exception
    .globl entry

entry:
    li $t0, 0xF
    sb $t0, 0x24000000($zero)
    jr $zero
