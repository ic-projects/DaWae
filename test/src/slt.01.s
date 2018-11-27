# ns4516
# SLT Check MIN_INT is less than MAX_INT
    .globl entry

entry:
    li $t0, 0xFFFFFFFF
    li $t1, 0x7FFFFFFF
    slt $v0, $t0, $t1
    jr $zero
