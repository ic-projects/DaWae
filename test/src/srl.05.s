# ns4516
# SLL -72 by 3
    .globl entry

entry:
    li $t0, -72
    srl $v0, $t0, 3
    jr $zero
