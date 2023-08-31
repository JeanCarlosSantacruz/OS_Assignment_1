#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
MAR: da posicion de memoria que hay que leer
MDR:
9 instrucciones:
SET, LDR, ADD
*/

/*
D0 = memory[0]
D1 = memory[1]
D2 = memory[2]
D3 = memory[3]
D4 = memory[4]
D5 = memory[5]
D6 = memory[6]
D7 = memory[7]
D8 = memory[8]
...
*/

int accumulator = 0;
char icr;
int mar = 0;
int mdr = 0;
char mdrc[20];
int memory[100]; // Memoria de 100 direcciones inicializada en 0
int pc = 100; /*El pc counter va a empezar desde la posicion 100 de la memoria*/
int alu = 0;
char cu[10]; //control unit
int Pmemory[100];

// Función para ejecutar la instrucción SET
void SET(int addr, int value) { 
  memory[addr] = value;
  mar = addr;
  mdr = memory[addr];
  memset(mdrc, '\0', sizeof(mdrc));
}

// Función para ejecutar la instrucción LDR
void LDR(int addr) { 
  accumulator = memory[addr];
  mar = addr;
  mdr = memory[addr];
  memset(mdrc, '\0', sizeof(mdrc));
}

// Función para ejecutar la instrucción ADD
void ADD(char *addr1, char *addr2, char *addr3) {
  if ((strcmp(addr3, "NULL") == 0) && (strcmp(addr2, "NULL") == 0)) {
    int pos = atoi(&addr1[1]);
    mar = pos;
    alu = accumulator;
    alu += memory[pos];
    accumulator = alu;
    mdr = memory[pos];
    memset(mdrc, '\0', sizeof(mdrc));
  } else if (strcmp(addr3, "NULL") == 0) {
    int bandera = 1;
    alu = 0;
    char* pos[2] = {addr1,addr2};
    for (int i = 0; i < 2; i++) {
      accumulator = memory[atoi(&pos[i][1])];
      mar = atoi(&pos[i][1]);
      alu += accumulator;
      mdr = memory[atoi(&pos[i][1])];
      memset(mdrc, '\0', sizeof(mdrc));
    }
    accumulator = alu;
  } else {
    int pos3 = atoi(&addr3[1]);
    char* pos[2] = {addr1,addr2};
    for (int i = 0; i < 2; i++) {
      accumulator = memory[atoi(&pos[i][1])];
      mar = atoi(&pos[i][1]);
      alu += accumulator;
      mdr = memory[atoi(&pos[i][1])];
      memset(mdrc, '\0', sizeof(mdrc));
    }
    accumulator = alu;
    memory[pos3] = accumulator;
    printf("%d\n", memory[pos3]);
  }
}

// Función para ejecutar la instrucción INC
void INC(int addr) { 
  memory[addr]++; 
  mar = addr;
  alu = memory[addr]++;
  mdr = memory[addr];
  memset(mdrc, '\0', sizeof(mdrc));
}

// Función para ejecutar la instrucción DEC
void DEC(int addr) { 
  memory[addr]--;
  mar = addr;
  alu = memory[addr]--;
  mdr = memory[addr];
  memset(mdrc, '\0', sizeof(mdrc));
}

// Función para ejecutar la instrucción STR
void STR(int addr) { 
  memory[addr] = accumulator;
  mar = addr;
  mdr = memory[addr];
  memset(mdrc, '\0', sizeof(mdrc));
}

void SHW(char *p1) {
  char token;
  token = *p1;
  if ( token == 'D'){
    printf("%d\n", memory[atoi(&p1[1])]);
  }
  else if( strcmp(p1, "MAR") == 0 ) {
    printf("%d\n", Pmemory[3]);
  } else if( strcmp(p1, "MDR") == 0 ) {
    if (mdr != 0){
      printf("%d\n", Pmemory[4]);
    } else {
      printf("%c\n", Pmemory[5]);
    }
  } else if( strcmp(p1, "PC") == 0 ) {
    printf("%d\n", Pmemory[0]);
  } else if( strcmp(p1, "ACCUMULATOR") == 0 ) {
    printf("%d\n", Pmemory[1]);
  } else if( strcmp(p1, "ICR") == 0 ) {
    printf("%c\n", Pmemory[2]);
  }
  
}

void PAUSE(int pause) {
  if (pause == 0) {
    Pmemory[0] = pc;
    Pmemory[1] = accumulator;
    Pmemory[2] = icr;
    Pmemory[3] = mar;
    Pmemory[4] = mdr;
    Pmemory[5] = *mdrc;
    pause++;
  } else if (pause == 1) {
    pause--;
  }
}

void END() {}

int main() {
  FILE *archivo = fopen("archivo.txt", "r");

  char linea[256];
  int pause = 0;

  while (fgets(linea, sizeof(linea), archivo) != NULL) {
    char ins[10];
    char p1[10];
    char p2[10];
    char p3[10];
    sscanf(linea, "%s %s %s %s", ins, p1, p2, p3);
    icr = *linea;
    mdr = 0;
    mar = pc;
    strncpy(mdrc, linea, 20);
    if (strcmp(ins, "PAUSE") == 0){
      strncpy(cu, mdrc, 5);
    } else{
      strncpy(cu, mdrc, 3);
    }
    //printf("%s\n",cu);
    //printf("comando %d, %d\n", i, accumulator);
    //printf("%s\n", p2);
    
    if (strcmp(cu, "SET") == 0) {
      int p2c = atoi(p2); /*Convierte la lista de chars en un entero*/
      int p1c = atoi(&p1[1]);
      SET(p1c, p2c);
    } else if (strcmp(cu, "LDR") == 0) {
      int p1c = atoi(&p1[1]);
      LDR(p1c);
    } else if (strcmp(cu, "ADD") == 0) {
      ADD(p1, p2, p3);
    } else if (strcmp(cu, "INC") == 0) {
      int p1c = atoi(&p1[1]);
      INC(p1c);
    } else if (strcmp(cu, "DEC") == 0) {
      int p1c = atoi(&p1[1]);
      DEC(p1c);
    } else if (strcmp(cu, "STR") == 0) {
      int p1c = atoi(&p1[1]);
      STR(p1c);
    } else if (strcmp(cu, "SHW") == 0) {
      SHW(p1);
    } else if (strcmp(cu, "PAUSE") == 0) {
      PAUSE(pause);
    } else if (strcmp(cu, "END") == 0) {
      END();
    }
    pc++;
  } /*cierra while*/

  fclose(archivo);

  return 0;
}
