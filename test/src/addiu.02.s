# ns4516
# Add -999 to 882 in $v0
    .globl entry

entry:
    li $v0, 882
    addiu $v0, $v0, -999
    jr $zero
