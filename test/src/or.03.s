# OR a mix of 1s and 0s
    .globl entry

entry:
    li $t1, 0x00AC
    li $t2, 0xB0D0
    or $v0, $t1, $t2
    jr $zero