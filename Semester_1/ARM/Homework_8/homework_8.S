//Aufgabe 2

//r2 = r1 + 7
//r6 = r1 * 32
//r6 = r1 * 17
//r9 = r0 - r4 : 16

ADD r2, r1, #7

MUL r6, r1, #32 //oder 
MOV r6, r1, LSL #5

MUL r6, r1, #17
MOV r6, r1, LSL #4
ADD r6, r6, #1

SUB r9, r0, r4, ASR #3

//Aufgabe 3
//a) LDR r0, =2480              --> 1001 1011 0000                              --> MOV r0, #155 LSL #4
//b) LDR r0, =1240              --> 0100 1101 1000                              --> MOV r0, #155 LSL #3
//c) LDR r0, =0xfa4fffff        --> 1111 1010 0100 1111 1111 1111 1111 1111     --> MVN r0, #91 LSL #20
//d) MOV r0, #0x5b, ROR #1      --> 0101 1011                                   --> MOV r0, #182 ROR #2


//pc        r0          r1
//0x0       ?           ?
//0x4       0x1         ?
//0x8       0x1         0x5
//0xC       0x6         0x5
//0x10      0x6         0x5
//0x8       0x6         0x5 
//wird nicht ausgeführt, da pointer auf 0x8 zeigt und von da weiter ausgeführt wird.
//0xC       0xB         0x5
//0x10      0xB         0x5
//0x14      0xB         0x5
//0x0       0xB         0x5
//0x4       0x1         0x5        


//0x0
//LDR r0, =0x1
//0x4
//LDR r1, =0x5
//0x8
//ADD r0, r0, r1
//0xC
//CMP r0, #0x8 --compare r0 und hex wert, wenn negativ --> Negative Flag gesetzt!
//0x10
//LDRLT pc, =0x8 --Wenn negative Flag gesetzt pc auf Hex wert.
//0x14
//MOV pc, #0
//0x18

