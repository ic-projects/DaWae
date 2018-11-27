# ns4516
# SLTI Check MIN_INT is less than 0x7FFF
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    slti $v0, $t0, 0x7FFF
    jr $zero
