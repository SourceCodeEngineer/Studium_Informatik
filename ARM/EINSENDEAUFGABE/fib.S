.global fib

fib:
  // die idee: wir starten mit der belegung der register, fibonacci von 0 ist 0; fibonacci von 1 = 1;

  // Rückgabewert:
  //   r0: Wert des groessten Array-Elements
  // Registerbelegung:
  //   r0: rückgabewert
  //   r1: fibonacci zahl von 0
  //   r2: fibonacci zahl von 1
  //   r3: zwischenspeicher von r2
  //   r4: eingegebene fibonacci zahl
  //   r5: unbenützt
  //   r6: unbenützt
  //   r7: unbenützt

STMFD sp!, {r1-r8, lr}     // register werden geladen
MOV r1, #0                 // move zahl 0 in das register r1
MOV r2, #1                 // move zahl 1 in das register r2
MOV r4, r0                 // kopiere die eingegebene fib zahl von register r0 in register r4
MOV r3, #0                 // register r3 wird auf 0 gesetzt

CMP r4, #1                 // compare register 4 mit 1 und flags setzen (entweder 0 flag oder negativ flag ist relevant)
MOVLS r2, r0               // wenn flags gesetzt move register r0 in register r2 da das ergebnis von fib 0 die zahl 0 ist und ansonsten das ergebnis von fib 1 die zahl 1 ist.
BLS endoffile              // sprung zu "endoffile" weil dann "f von n" gleich "n" ist

myfunction:
                           // funktion zum rekursiven aufruf von fibonacci zahlen
    SUB r4, r4, #1         // subtrahiere den wert 1 vom register 4 um somit auf n -1 zu kommen
    MOV r3,r2              // register 2 wird in register 3 zwischengespeichert
    ADD r2, r1, r2         // nun wird bei dem register r2 der wert von register r1 dazugezählt
    MOV r1,r3              // das register r1 bekommt nun den wert vom register r3 was das alte register r2 ist

    CMP r4, #1             // compare ob der wert im register r4 gößer ist als 1 und flags setzen
    BHI myfunction         // wieder von vorne       
    B endoffile            // wenn die rekursion beendet wurde, sprung zu "endoffile"

endoffile:

    MOV   r0, r2           // r0 wird zu r2, da r0 der rückgabewert ist und r2 das Ergebnis der fibonacci folge
    LDMFD sp!, {r1-r8,pc}  // "sicherung" der register
    MOV pc, lr
