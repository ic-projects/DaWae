# ns4516
# LHU 0x8F from 0x200000FF and check not sign extended
    .globl entry

entry:
    li $t0, 0x200000FF
    li $t1, 0x008F      #0000000010001111
    sh $t1, 0($t0)
    lhu $v0, 0($t0)     #v0 = 00000000000000000000000010001111
    srl $v0, 4          #v0 = 0...00001000
    jr $zero            #exit = 00001000 = 8
