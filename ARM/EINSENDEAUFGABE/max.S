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
CMP r3, #0                 // vergleicht ob die länge des arrays 0 ist und setzt dann die zero flag
BEQ endoffile              // wenn zero flag gesetzt wurde, wird das file zu endoffile springen
  
myloop:     
                           // in der schleife wird das aktuelle element mit dem darauf folgenden element verglichen und somit das maximum ermittelt.
    LDR r5, [r2]           // lade das element das jetzt dran ist 
    CMP r4, r5             // schaue ob das nächste Element größer ist als der Vorgänger
    MOVLT r4, r5           // wenn es größer ist dann wird das element getauscht.
    ADD r2, r2, #4         // gehe zum nächstem Element des arrays  
    SUBS r3, r3, #1        // subtrahiere 1 von der Länge da wir beim nächsten element sind und setzt die flags
    BNE myloop             

endoffile:

    MOV r0, r4             // move MAX in den rückgabewert
    LDMFD sp!, {r2-r5, pc} // "Sicherung" der Register r2-r5
    MOV pc, lr             // rücksprung ("return")
