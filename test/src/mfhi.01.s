# ns4516
# Move uninitialised value of HI to $v0
    .globl entry

entry:
    mfhi $v0
    jr $zero
