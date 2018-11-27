# ns4516
# SLL all 1s by 32
    .globl entry

entry:
    li $v0, 0xFFFFFFFF
    sll $v0, 32
    jr $zero
