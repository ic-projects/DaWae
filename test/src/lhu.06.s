# ns4516
# LHU from invalid memory address 0x23FFFFFF
    .globl entry

entry:
    li $t0, 0x23FFFFFF
    lhu $v0, 0($t0)
    jr $zero
