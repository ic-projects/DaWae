# ns4516
# SB 0xF in 0x4000000 with no offset without crashing
    .globl entry

entry:
    li $t0, 0x4000000
    li $t1, 0xF
    sb $t1, 0($t0)
    jr $zero
