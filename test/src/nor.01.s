li $t1, 0xFFFF
li $t2, 0x0
nor $v0, $t1, $t2
sw $v0, 0x30000004($zero)