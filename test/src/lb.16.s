# ns4516
# LB 0x8F from 0x20000000 and check sign extended
    .globl entry

entry:
    li $t0, 0x20000000
    li $t1, 0x8F        #10001111
    sb $t1, 0($t0)
    lb $v0, 0($t0)      #v0 = 111111111111111110001111
    srl $v0, 4          #v0 = 111111111111111111111000
    jr $zero            #exit = 11111000 = 248

