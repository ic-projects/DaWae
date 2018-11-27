# ns4516
# SLTUI Check 0xFFFFFFFF isn't less than 0x7FFF
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    sltiu $v0, $t0, 0x7FFF
    jr $zero
