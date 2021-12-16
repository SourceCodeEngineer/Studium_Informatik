.global max
.global min
.global sum
.global fold

.align
.text
fold: // TODO
  // Argumente:
  //   r0: Anfangswert
  //   r1: Adresse des Arrays
  //   r2: Länge des Arrays
  //   r3: Aggregator (Funktionszeiger)
  // Rückgabewert:
  //   r0: Akkumulator

MOV pc, lr

agg_max: // fertig
  // Argumente:
  // r0: Akkumulator
  // r1: Element
  // Rückgabewert:
  // r0: Akkumulator

CMP r1, r0
MOVGT r0, r1
MOV pc, lr

max: // fertig
  // Argumente:
  //   r0: Array Adresse
  //   r1: Array Länge
  // Rückgabewert:
  //   r0: Wert des groessten Array-Elements
  
MOV r2, r1
MOV r1, r0
LDR r0, [r1]
LDR r3, =agg_max
B fold

agg_min: // TODO
  // Argumente:
  // r0: Akkumulator
  // r1: Element
  // Rückgabewert:
  // r0: Akkumulator
MOV pc, lr

min: // fertig
  // Argumente:
  //   r0: Array Adresse
  //   r1: Array Länge
  // Rückgabewert:
  //   r0: Wert des kleinsten Array-Elements

MOV r2, r1
MOV r1, r0
LDR r0, [r1]
LDR r3, =agg_min
B fold

agg_sum: // TODO
  // Argumente:
  // r0: Akkumulator
  // r1: Element
  // Rückgabewert:
  // r0: Akkumulator

MOV pc, lr

sum: // fertig
  // Argumente:
  //   r0: Array Adresse
  //   r1: Array Länge
  // Rückgabewert:
  //   r0: Summe der Array-Elemente

MOV r2, r1
MOV r1, r0
MOV r0, #0
LDR r3, =agg_sum
B fold
