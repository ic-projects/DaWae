# OR a number against 1s to get itself
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x00AA0020
    or $v0, $t0, $t1
    jr $zero