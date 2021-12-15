.global fib

fib:
  // die idee: wir starten mit der belegung der register, fibonacci von 0 ist 0; fibonacci von 1 = 1;

  // Rückgabewert:
  //   r0: Wert des groessten Array-Elements
  // Registerbelegung:
  //   r0: rückgabewert
  //   r1: fibonacci zahl von 0
  //   r2: fibonacci zahl von 1
  //   r3: rückgabewert der summe der fib zahlen
  //   r4: eingegebene zahl
  //   r5: summe der fibonacci zahlen

STMFD sp!, {r1-r8, lr}     // register werden geladen
MOV r1, #0                 // move zahl 0 in das register r1
MOV r2, #1                 // move zahl 1 in das register r2
MOV r4, r0                 // kopiere die eingegebene fib zahl von register r0 in register r4

CMP r4, #1                 // vergleichen ob n kleiner oder gleich 1 ist und flags setzen
MOVLS r3, r0               // dann bleibt n gleich
BLS endoffile              // dann f(n) gleich n

myfunction:
    

endoffile:
    MOV   r0, r3           // r0 wird zu r2, da r0 der rückgabewert ist und r2 das Ergebnis der fibonacci folge
    LDMFD sp!, {r1-r8,pc}  // "sicherung" der register
    MOV pc, lr
