# ns4516
# SRL all 1s by 31, inserting 0s
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    srl $v0, $t0, 31
    jr $zero
