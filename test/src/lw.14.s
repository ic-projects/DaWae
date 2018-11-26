# ns4516
# LW from 0x10FFFFFD (1 above exec mem) causing exception
    .globl entry

entry:
    li $t0, 0x10FFFFFD
    lw $v0, 0($t0)
    jr $zero
