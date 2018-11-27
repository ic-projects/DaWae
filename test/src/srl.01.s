# ns4516
# SRL 128 by 3
    .globl entry

entry:
    li $v0, 128
    srl $v0, $v0, 3
    jr $zero
