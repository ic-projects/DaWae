# ns4516
# SLL all 1s by 31
    .globl entry

entry:
    li $v0, 0xFFFFFFFF
    sll $v0, 31
    jr $zero
