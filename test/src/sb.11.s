# ns4516
# SB to 0x30000000 (mapped input mem) which is read only
    .globl entry

entry:
    li $t0, 0xFF
    sb $t0, 0x30000000($zero)
    jr $zero
