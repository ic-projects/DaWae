# ns4516
# SB 0xFF in 0x23FFFFFF(max addr) without exception
    .globl entry

entry:
    li $t0, 0xFF
    sb $t0, 0x23FFFFFF($zero)
    jr $zero
