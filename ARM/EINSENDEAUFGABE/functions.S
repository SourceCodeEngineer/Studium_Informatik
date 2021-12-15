.global max

max:
  // Argumente:
  //   r0: Array Adresse
  //   r1: Array Länge
  // Rückgabewert:
  //   r0: Wert des groessten Array-Elements
  // Registerbelegung:
  //   r2: Adresse des Arrays
  //   r3: Länge des Arrays
  //   r4: Momentan Größtes
  //   r5: derzeitiges Element

STMFD sp!, {r2-r5, lr}     // register werden geladen
MOV r2, r0                 // kopiert die adresse vom array in das register r2
MOV r3, r1                 // kopieren die länge des arrays in das register r5
LDR r4, [r2]               // wähle das erste element als startpunkt für den "max" wert
CMP r3, #0                 // vergleicht die länge des arrays mit 0 und setzt die flags automatisch
BEQ endoffilemax           // wenn eine zero flag gesetzt wurde, wird das file zu endoffilemax springen

myloopmax:
                           // in der schleife wird das aktuelle element mit dem darauf folgenden element verglichen und somit das maximum ermittelt.
    LDR r5, [r2]           // lade das element das jetzt dran ist
    CMP r4, r5             // schaue ob das nächste element größer ist als der vorgänger
    MOVLT r4, r5           // wenn es größer ist dann wird das element getauscht.
    ADD r2, r2, #4         // gehe zum nächstem element des arrays
    SUBS r3, r3, #1        // subtrahiere 1 von der länge da wir beim nächsten element sind und setzt die flags
    BNE myloopmax

endoffilemax:

    MOV r0, r4             // move MAX in den rückgabewert
    LDMFD sp!, {r2-r5,pc}  // "Sicherung" der register r2-r5
    MOV pc, lr             // Rücksprung ("return")

.global min

min:
  // Argumente:
  //   r0: Array Adresse
  //   r1: Array Länge
  // Rückgabewert:
  //   r0: Wert des kleinsten Array-Elements
  // Registerbelegung:
  //   r6: Adresse des Arrays
  //   r7: Länge des Arrays
  //   r8: Momentan Kleinstes
  //   r9: derzeitiges Element

STMFD sp!, {r2-r5, lr}     // register werden geladen
MOV r6, r0                 // move array adresse in register 6
MOV r7, r1                 // move array länge in register 7
LDR r8, [r6]               // wähle das erste element als startpunkt für den "min" wert
CMP r7, #0                 // vergleiche r7 mit 0 und die flags werden gesetzt
BEQ endoffilemin           // wenn zero flag gesetzt, sprung zu endoffilemin

myloopmin:
                           // in der schleife wird das aktuelle element mit dem darauf folgenden element verglichen und somit das minimum ermittelt.
    LDR r9, [r6]           // lade das element das jetzt dran ist
    CMP r8, r9             // schaue ob das nächste element kleiner ist als der vorgänger
    MOVGT r8, r9           // wenn es kleiner ist dann wird das element getauscht.
    ADD r6, r6, #4         // gehe zum nächstem element des arrays
    SUBS r7, r7, #1        // subtrahiere 1 von der Länge da wir beim nächsten element sind
    BNE myloopmin

endoffilemin:

    MOV r0, r8             // move MIN in den rückgabewert
    LDMFD sp!, {r6-r9,pc}  // "Sicherung" der Register r6-r9
    MOV pc, lr             // Rücksprung ("return")

.global sum

sum:
  // Argumente:
  //   r0: Array Adresse
  //   r1: Array Länge
  // Rückgabewert:
  //   r0: Wert der Summe der Array-Elemente
  // Registerbelegung:
  //   r2: adresse des arrays
  //   r3: länge des arrays
  //   r4: momentane summe bis zum jetzigen element
  //   r5: derzeitiges element

STMFD sp!, {r2-r5, lr}    // register werden geladen
MOV r2, r0                // move array adresse in register 2
MOV r3, r1                // move array länge in register 1
LDR r4, [r2]              // wähle das erste element als startpunkt für den "sum" wert
CMP r3, #0			          // hier wird verglichen ob das register r3 0 ist und flags werden gesetzt
BEQ endoffilesum

myloopsum:
                          // die schleife ermittelt den wert von 2 zahlen
    ADD r2, r2, #4        // wir haben bereits die summe des 1. elements und können nun zum 2. element gehen
    LDR r5, [r2]          // das register r5 wird zum alten element was unsere summe ist
    ADD r4, r4, r5        // nun addieren wir die alte summe in r5 und die neue zahl zusammen und speichern das in r5 ab
    SUBS r3, r3, #1       // länge des arrays wird um 1 verringert und die flags werden gesetzt
    BNE myloopsum         // wenn die länge 0 ist dann wurden alle elemente aus dem array zusammengezählt.

endoffilesum:

MOV r0, r4                // move register r4 (unsere sume) in den Rückgabewert
LDMFD sp!, {r2-r5,pc}     // "Sicherung" der Register r2-r5
MOV pc, lr                // Rücksprung ("return")
