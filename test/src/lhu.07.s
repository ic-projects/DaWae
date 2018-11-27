# ns4516
# LHU from read only memory address 0x10000000
    .globl entry

entry:
    li $t0, 0x10000000
    lhu $t1, 0($t0)
    jr $zero
