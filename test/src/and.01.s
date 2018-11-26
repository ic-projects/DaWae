# ns4516
# AND 0xAA against 0s to get 0s
    .globl entry

entry:
    li $t0, 0x0
    li $t1, 0xAA
    and $v0, $t0, $t1
    jr $zero
