# ns4516
# Load 0xFFFFFFFF into LO and retrieve
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    mtlo $t0
    mflo $v0
    jr $zero
