# ns4516
# SLL all 1s by 31
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    sll $v0, $t0, 31
    jr $zero
