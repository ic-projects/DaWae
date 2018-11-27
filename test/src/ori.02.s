# ns4516
# ORI 0xFFFFFFFF and 0xAA20 to get 1s
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    ori $v0, $t0, 0xAA20
    jr $zero
