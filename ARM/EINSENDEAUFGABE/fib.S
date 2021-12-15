

.global fib
//tipp :Die Fibonacci-Folge ist eine unendliche Folge von Zahlen, bei der sich die jeweils folgende Zahl durch Addition ihrer beiden vorherigen fibonacci Zahlen ergibt:  

   
fib:
        STMFD sp!, {r1-r8, lr}
                                  
        MOV r1, #0                       //Anfgangswert der Fibonacci Zahlen 0,1
        MOV r2, #1                       
        MOV r4, r0      
        
                                                               
        


        CMP r4, #1              //n kleiner gleich 1
        MOVLS r2, r0            //dann bleibt n gleich
        BLS exit                 // dann f(n) gleich n

        
        
        
function:                      //es werden rekursiv immer die Vorgänger zusammengezählt
                                       
       SUB r4, r4, #1          //n -1
       MOV r7,r2               //r7 bekommt den Wert von r2
       ADD r2, r1, r2          //bei r2 wird der Wert von r1 dazugezählt siehe tipp
       MOV r1,r7               //r1 bekommt den Wert von r7(altes r2) 
      

       CMP r4, #1             //r5 grösser als eins
       BHI function           //wieder von vorne       
       B exit
                  

                                     
exit: 
        MOV   r0, r2         // r0 wird zu r2, da r0 der rückgabewert ist und r2 das Ergebnis der fibonacci folge 
        LDMFD sp!, {r1-r8,pc}
        MOV pc, lr

