# ns4516
# SB 0xF in 0x23FFFFFF(max addr) without exception
    .globl entry

entry:
    li $t0, 0xF
    sb $t0, 0x23FFFFFF($zero)
    jr $zero
