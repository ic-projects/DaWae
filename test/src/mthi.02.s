# ns4516
# Load 0xFFFFFFFF into HI and retrieve
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    mthi $t0
    mfhi $v0
    jr $zero
