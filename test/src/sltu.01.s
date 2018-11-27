# ns4516
# SLTU Check 0xFFFFFFFF isn't less than 0x7FFFFFFF
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x7FFFFFFF
    sltu $v0, $t0, $t1
    jr $zero
