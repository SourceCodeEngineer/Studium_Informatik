.global max

// alle kommentare sind in deutsch und in englisch neben den zeilen kommentiert worden für die bessere lesbarkeit des kontrolleurs (und auch damit plagiatsvorwürfe abgewehrt werden können).
// bitte beachten, dass der einfachkeit halber, alle kommentare in kleinschreibung sind. rechtschreibfehler sind vorbehalten!
// deutsche version hinzugefügt am 16.12.2021 - englische version hinzugefügt am 18.12.2021

// all comments are in german and then after that in english as well for more readability of the controller of the given tasks.
// please note that for the sake of simplicity, all comments are in lower case. Spelling mistakes are reserved!
// german version added on the 16th of dezember 2021 - englisch version added on the 18th of dezember 2021

max:
  // Argumente:                                  // arguments:
  //   r0: Array Adresse                         //   r0: array address
  //   r1: Array Länge                           //   r1: array length
  // Rückgabewert:                               // returnvalue:
  //   r0: Wert des groessten Array-Elements     //   r0: value of the greatest array element
  // Registerbelegung:                           // register allocation:
  //   r2: adresse des arrays                    //   r2: address of the array
  //   r3: länge des arrays                      //   r3: length of the array
  //   r4: momentan größtes element              //   r4: current greatest element in terms of value
  //   r5: derzeitiges element                   //   r5: current element

STMFD sp!, {r2-r5, lr}     // register werden gesichert                                                 // registers are being saved
MOV r2, r0                 // kopiert die adresse vom array in das register r2                          // copy the address of the array to register r2
MOV r3, r1                 // kopieren die länge des arrays in das register r5                          // copy the length of the array to register r5
LDR r4, [r2]               // wähle das erste element als startpunkt für den "max" wert                 // set the first element of the array as my starting point for the max value

CMP r3, #0                 // vergleicht die länge des arrays mit 0 und setzt die flags automatisch     // compares the length of the array with 0 and sets the flags automatically
BEQ endoffilemax           // wenn eine zero flag gesetzt wurde, wird das file zu endoffilemax springen // if an zero flag is present then we will jump to the endoffilemax

myloopmax:
                           // in der schleife wird das aktuelle element mit dem darauf folgenden element verglichen und somit das maximum ermittelt. // the current element will be compared to the next element and so we will define the max value in this loop
    LDR r5, [r2]           // lade das element das jetzt dran ist                                                                                    // load the element that will be compared now
    CMP r4, r5             // schaue ob das nächste element größer ist als der vorgänger                                                             // look if the current element is greater than the element before
    MOVLT r4, r5           // wenn es größer ist dann wird das element getauscht.                                                                    // if the element is greater, then iw will be swapped
    ADD r2, r2, #4         // gehe zum nächstem element des arrays                                                                                   // go to the next element of the array
    SUBS r3, r3, #1        // subtrahiere 1 von der länge, da wir beim nächsten element sind und setzt die flags                                     // subtract 1 from the length because we are at the next element and set the flags
    BNE myloopmax

endoffilemax:

    MOV r0, r4             // move MAX in den rückgabewert           // move MAX in the return value
    LDMFD sp!, {r2-r5,pc}  // "wiederherstellung" der register r2-r5 // "restore" the registers r2-r5
    MOV pc, lr             // Rücksprung ("return")                  // return

.global min

min:
  // Argumente:                              // arguments:
  //   r0: Array Adresse                     //   r0: array address
  //   r1: Array Länge                       //   r1: array length
  // Rückgabewert:                           // return value:
  //   r0: Wert des kleinsten Array-Elements //   r0: value of the smallest array element
  // Registerbelegung:                       // register allocation:
  //   r7: länge des arrays                  //   r7: length of the array
  //   r8: momentan kleinstes element        //   r8: currently smallest element
  //   r9: derzeitiges Element               //   r9: current element

STMFD sp!, {r2-r5, lr}     // register werden geladen                                   // registers are being loaded
MOV r6, r0                 // move array adresse in register 6                          // move array address to register r6
MOV r7, r1                 // move array länge in register 7                            // move array length to register r7
LDR r8, [r6]               // wähle das erste element als startpunkt für den "min" wert // set the first element of the array as my starting point for the min value

CMP r7, #0                 // vergleiche register r7 mit 0 und die flags werden gesetzt // compare if register r7 is 0 and set the flags
BEQ endoffilemin           // wenn zero flag gesetzt, sprung zu endoffilemin            // if the zero flag is set, jump to endoffilemin

myloopmin:
                           // in der schleife wird das aktuelle element mit dem darauf folgenden element verglichen und somit das minimum ermittelt. // in the loop, the current element is compared with the following element and the minimum is thus determined
    LDR r9, [r6]           // lade das element das jetzt dran ist                                                                                    // load the element that will be compared now
    CMP r8, r9             // schaue ob das nächste element kleiner ist als der vorgänger                                                            // see if the next element is smaller than the previous one
    MOVGT r8, r9           // wenn es kleiner ist dann wird das element getauscht.                                                                   // if it is smaller then the element is exchanged
    ADD r6, r6, #4         // gehe zum nächstem element des arrays                                                                                   // go to the next element of the array
    SUBS r7, r7, #1        // subtrahiere 1 von der Länge da wir beim nächsten element sind  und flags setzen                                        // subtract 1 from the length since we are on the next element and set the flags
    BNE myloopmin

endoffilemin:

    MOV r0, r8             // move MIN in den rückgabewert           // m ove MIN to the return value register r0
    LDMFD sp!, {r6-r9,pc}  // "wiederherstellung" der register r6-r9 // restore the registers r6-r9
    MOV pc, lr             // Rücksprung ("return")                  // return

.global sum

sum:
  // Argumente:                                     // arguments:
  //   r0: Array Adresse                            //   r0: array address
  //   r1: Array Länge                              //   r1: array length
  // Rückgabewert:                                  // return value:
  //   r0: Wert der Summe der Array-Elemente        //   r0: value of the sum of all the array elements
  // Registerbelegung:                              // register allocation:
  //   r2: adresse des arrays                       //   r2: address of the array
  //   r3: länge des arrays                         //   r3: length of the array
  //   r4: momentane summe bis zum jetzigen element //   r4: current sum up to the current element
  //   r5: derzeitiges element                      //   r5: current element

STMFD sp!, {r2-r5, lr}    // register werden gesichert                                              // registers are saved
MOV r2, r0                // move array adresse in register r2                                      // move array address to register r2
MOV r3, r1                // move array länge in register r1                                        // move array length to register r1
LDR r4, [r2]              // wähle das erste element als startpunkt für den "sum" wert              // set the first element as the starting point for the sum value

CMP r3, #0			          // hier wird verglichen ob das register r3 0 ist und flags werden gesetzt // compare r3 with 0 and set the flags
BEQ endoffilesum

myloopsum:
                          // die schleife ermittelt den wert von 2 zahlen                                                                  // the loop will return the value of 2 numbers
    ADD r2, r2, #4        // wir haben bereits die summe des 1. elements und können nun zum 2. element gehen                               // we do already have the sum of the 1st element and now we can go to the 2nd element
    LDR r5, [r2]          // das register r5 wird zum alten element was unsere summe ist                                                   // the register r5 is going to be our placeholder for the current sum
    ADD r4, r4, r5        // nun addieren wir die alte summe in register r5 und die neue zahl zusammen und speichern das in register r4 ab // now we add register r5 to register r4 as well as the value that is already in register r4
    SUBS r3, r3, #1       // länge des arrays wird um 1 verringert und die flags werden gesetzt                                            // length of the array will be reduced by 1 and the flags will be set
    BNE myloopsum         // wenn die länge 0 ist dann wurden alle elemente aus dem array zusammengezählt.                                 // if the length is 0, then all elements of the array are summed up.

endoffilesum:

MOV r0, r4                // move register r4 (unsere sume) in den Rückgabewert // move register r4 (our sum) to the return value
LDMFD sp!, {r2-r5,pc}     // "wiederherstellung" der register r2-r5             // "restore" the registers r2-r5
MOV pc, lr                // Rücksprung ("return")                              // return
