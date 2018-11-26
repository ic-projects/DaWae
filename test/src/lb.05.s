# ns4516
# LB from uninitialised 0x20000000 with 0x3FFFFFF offset
    .globl entry

entry:
    li $t0, 0x20000000
    lb $v0, 0x3FFFFFF($t0)
    jr $zero
