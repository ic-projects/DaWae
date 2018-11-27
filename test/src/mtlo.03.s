# ns4516
# Load 144 into LO and retrieve
    .globl entry

entry:
    li $t0, 144
    mtlo $t0
    mflo $v0
    jr $zero
