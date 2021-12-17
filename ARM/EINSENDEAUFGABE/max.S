.global max

// alle kommentare sind in deutsch und in englisch neben den zeilen kommentiert worden für die bessere lesbarkeit des kontrolleurs (und auch damit plagiatsvorwürfe abgelehnt werden können).
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
