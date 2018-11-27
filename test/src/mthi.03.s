# ns4516
# Load 144 into HI and retrieve
    .globl entry

entry:
    li $t0, 144
    mthi $t0
    mfhi $v0
    jr $zero
