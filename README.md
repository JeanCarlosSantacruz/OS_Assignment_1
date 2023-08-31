# OS_Assignment_1


Se realizo un codigo en C, que simula el siguiente conjunto de instrucciones:

SET - MEM - SET D1 X NULL NULL, Store X value in D1 memory address. where X is an
immediate, direct or constant value. When SET instruction is read the X value is stored in
Memory without processor execution.

LDR - LOAD - LDR D3 NULL NULL Load the value in D3 memory address and puts in
accumulator register

ADD - ADDITION - There are three ways: ADD D1 NULL NULL, adds the value in D1
memory address to loaded value in accumulator register. ADD D1 D3 NULL Load the
value in D1 memory address in the accumulator register and add to found value in D3
memory address. ADD D1 D3 D4 same that ADD D1 D3 but puts the result in D4

INC - INCREMENT - INC D3 NULL NULL Load the value in D3 memory address adds 1
and store in same address

DEC - DECREMENT - DEC D3 NULL NULL Load the value in D3 memory address adds 1
and store in same address

STR - STORE - STR D3 NULL NULL Read the value in accumulator register and puts in
D3 memory address

SHW - SHOW - SHW D2 NULL NULL show the value in D2 memory address, SHW ACC
show the value in accumulator register, SHW ICR show the value in ICR register, SHW
MAR show the value in MAR register, SHW MDR show the value in MDR register, SHW
UC show the value in Control Unit.

PAUSE - PAUSE - PAUSE NULL NULL NULL stop the instruction cycle and allow SHOW
register values and memory values at any time

END - FINISH READING INSTRUCTION

El simulador es capaz de leer archivos de texto plano con instrucciones ejecutables, del
"input.txt".

Para tener en cuenta:

** Solo se ejecuta un programa a la vez.
** Se implemento la memoria principal como un arreglo.
** Se implemento cada uno de los registro de la CPU a forma de variables.
