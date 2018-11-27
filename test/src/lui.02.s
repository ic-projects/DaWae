# ns4516
# LUI 0x9A1C into $v0 and shift 16 to check
    .globl entry

entry:
    lui $t0, 0x9A1C
    srl $v0, $t0, 16
    jr $zero
