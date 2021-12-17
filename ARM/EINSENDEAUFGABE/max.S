.global max

// alle kommentare sind in deutsch und in englisch neben den zeilen kommentiert worden für die bessere lesbarkeit des kontrolleurs (und auch damit plagiatsvorwürfe abgelehnt werden können).
// bitte beachten, dass der einfachkeit halber, alle kommentare in kleinschreibung sind. rechtschreibfehler sind vorbehalten!
// deutsche version hinzugefügt am 16.12.2021 - englische version hinzugefügt am 18.12.2021

// all comments are in german and then after that in english as well for more readability of the controller of the given tasks.
// please note that for the sake of simplicity, all comments are in lower case. Spelling mistakes are reserved!
// german version added on the 16th of dezember 2021 - englisch version added on the 18th of dezember 2021

max:
  // Argumente:
  //   r0: Array Adresse
  //   r1: Array Länge
  // Rückgabewert:
  //   r0: Wert des groessten Array-Elements
  // Registerbelegung:
  //   r2: adresse des arrays
  //   r3: länge des arrays
  //   r4: momentan größtes element
  //   r5: derzeitiges element

STMFD sp!, {r2-r5, lr}     // register werden geladen
MOV r2, r0                 // kopiert die adresse vom array in das register r2
MOV r3, r1                 // kopieren die länge des arrays in das register r5
LDR r4, [r2]               // wähle das erste element als startpunkt für den "max" wert
CMP r3, #0                 // vergleicht ob die länge des arrays 0 ist und setzt dann die zero flag
BEQ endoffile              // wenn zero flag gesetzt wurde, wird das file zu endoffile springen

myloop:
                           // in der schleife wird das aktuelle element mit dem darauf folgenden element verglichen und somit das maximum ermittelt.
    LDR r5, [r2]           // lade das element das jetzt dran ist
    CMP r4, r5             // schaue ob das nächste element größer ist als der vorgänger
    MOVLT r4, r5           // wenn es größer ist dann wird das element getauscht.
    ADD r2, r2, #4         // gehe zum nächstem element des arrays
    SUBS r3, r3, #1        // subtrahiere 1 von der länge da wir beim nächsten element sind und setzt die flags
    BNE myloop

endoffile:

    MOV r0, r4             // move MAX in den rückgabewert
    LDMFD sp!, {r2-r5, pc} // "sicherung" der register
    MOV pc, lr             // Rücksprung ("return")
