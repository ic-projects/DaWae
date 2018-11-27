# ns4516
# Move uninitialised value of LO to $v0
    .globl entry

entry:
    mflo $v0
    jr $zero
