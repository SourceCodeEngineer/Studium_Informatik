.global fib

// alle kommentare sind in deutsch und in englisch neben den zeilen kommentiert worden für die bessere lesbarkeit des kontrolleurs (und auch damit plagiatsvorwürfe abgewehrt werden können).
// bitte beachten, dass der einfachkeit halber, alle kommentare in kleinschreibung sind. rechtschreibfehler sind vorbehalten!
// deutsche version hinzugefügt am 16.12.2021 - englische version hinzugefügt am 18.12.2021

// all comments are in german and then after that in english as well for more readability of the controller of the given tasks.
// please note that for the sake of simplicity, all comments are in lower case. Spelling mistakes are reserved!
// german version added on the 16th of dezember 2021 - englisch version added on the 18th of dezember 2021

fib:
  // Rückgabewert:                    // return value:
  //   r0: fib zahl zu berechnen      //   r0: fib number to calculate
  // Registerbelegung:                // register allocation:
  //   r0: rückgabewert               //   r0: return value
  //   r1: fibonacci zahl von 0       //   r1: fibonacci number of 0
  //   r2: fibonacci zahl von 1       //   r2: fibonacci number of 1
  //   r3: zwischenspeicher von r2    //   r3: cache of r2
  //   r4: eingegebene fibonacci zahl //   r4: entered fibonacci number to calculate
  //   r5: unbenützt                  //   r5: unused
  //   r6: unbenützt                  //   r6: unused
  //   r7: unbenützt                  //   r7: unused

STMFD sp!, {r1 - r4, lr}   // register werden gesichert                                                                                                                        // registers are stored
MOV r1, #0                 // move zahl 0 in das register r1                                                                                                                   // move number 0 to register r1
MOV r2, #1                 // move zahl 1 in das register r2                                                                                                                   // move number 1 to register r2
MOV r4, r0                 // kopiere die eingegebene fib zahl von register r0 in register r4                                                                                  // copy the entered fibonacci number to calculate from register r0 to register r4
MOV r3, #0                 // register r3 wird auf 0 gesetzt                                                                                                                   // set register r3 to 0

CMP r4, #1                 // compare register r4 mit der zahl 1 und flags setzen (zero flag und negativ flag ist relevant)                                                    // compare register r4 with the number 1 and set the flags (the zero flag and the negative flag is relevant)
MOVLS r2, r0               // wenn flags gesetzt move register r0 in register r2 da das ergebnis von fib 0 die zahl 0 ist und ansonsten das ergebnis von fib 1 die zahl 1 ist. // if flags are set, move register r0 to register r2 because the answer to the given number 0 is 0 and the answer to the input 1 is 1
BLS endoffile              // sprung zu "endoffile" weil dann "f von n" gleich "n" ist                                                                                         // jump to "endoffile" because "f of n" is equal to "n"

myfib:
                           // funktion zum rekursiven aufruf von fibonacci zahlen                               // function for the recursive call of the fibonacci sequence
    SUB r4, r4, #1         // subtrahiere den wert 1 vom register r4 um somit auf n -1 zu kommen                // subtract 1 from register r4 to get n -1
    MOV r3,r2              // register r2 wird in register r3 zwischengespeichert                               // register r2 is cached in register r3
    ADD r2, r1, r2         // nun wird bei dem register r2 der wert von register r1 dazugezählt                 // now we add register r1 to register r2
    MOV r1,r3              // das register r1 bekommt nun den wert vom register r3 was das alte register r2 ist // the register r1 is now assigned the value of register r3 which was the old register r2

    CMP r4, #1             // compare ob der wert im register r4 gößer ist als 1 und flags setzen               // compare if the in register r4 is greater 1 and set the flags
    BHI myfib              // rückkehr zum beginn der schleife                                                  // back to the beginning of the loop
    B endoffile            // wenn die rekursion beendet wurde, sprung zu "endoffile"                           // if the rekursion is finished, jump to "endoffile"

endoffile:

    MOV   r0, r2             // kopiere das register r2 in das register r0 weil das der rückgabewert der eingegebenen fibonacci nummer ist // move register r2 to register r0 because register r0 is the return value of the given fibonacci number
    LDMFD sp!, {r1 - r4, pc} // "wiederherstellung" der register                                                                           // "restore" registers
    MOV pc, lr
