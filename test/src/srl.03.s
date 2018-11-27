# ns4516
# SRL all 1s by 31
    .globl entry

entry:
    li $v0, 0xFFFFFFFF
    srl $v0, 31
    jr $zero
