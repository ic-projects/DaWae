# ns4516
# SH 0xFFFF in 0x23FFFFFF with exception
    .globl entry

entry:
    li $t0, 0xFFFF
    sh $t0, 0x23FFFFFF($zero)
    jr $zero
