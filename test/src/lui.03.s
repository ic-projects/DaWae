# ns4516
# LUI 0x9A1C into $v0 and shift 24 to check
    .globl entry

entry:
    lui $t0, 0x9A1C
    srl $v0, $t0, 24
    jr $zero
