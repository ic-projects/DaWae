# ns4516
# SB 0xFF in 0x24000000 with exception
    .globl entry

entry:
    li $t0, 0xFF
    sb $t0, 0x24000000($zero)
    jr $zero
