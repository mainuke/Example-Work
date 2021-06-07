/*Manuel Iribarren CMSC216 Fall 2019 UID 114751782 Project #3 submitted 9/30/19
    This program implements the Coffee Cake CPU functions as listed in
    machine.h, which simulates the assembly instructions in said CPU*/
#include <stdio.h>
#include "machine.h"

int print_instruction(Word instruction) {
  unsigned int mask= 0, mem_address= 0, opcode= 0, register1= 0, register2= 0,
  register3= 0;

  mask = 15; /*Sets 4 bits to 1*/
  opcode = instruction>>28 & mask; /*Isolates value of opcode*/

  mask = 524287; /*Sets 19 bits to 1*/
  mem_address = instruction>>9 & mask; /*Isolates value of memory address*/

  mask = 7; /*Sets 3 bits to 1*/
  register1 = instruction>>6 & mask; /*Isolates value of the first register*/
  register2 = instruction>>3 & mask; /*Isolates value of second register*/
  register3 = instruction & mask; /*Isolates value of third register*/

  /*This segment first checks the validity of the instruction, then prints the
  corresponding outputs based on opcode ASSUMING the instructions are valid*/
  if (is_valid_instruction(instruction)) {
    if (opcode == PLUS) { /*Prints 3 registers*/
      printf("plus   R%d  R%d  R%d", register1, register2, register3);
    }
    else if (opcode == DIFF) { /*Prints 3 registers*/
      printf("diff   R%d  R%d  R%d", register1, register2, register3);
    }
    else if (opcode == MULT) { /*Prints 3 registers*/
      printf("mult   R%d  R%d  R%d", register1, register2, register3);
    }
    else if (opcode == QUOT) { /*Prints 3 registers*/
      printf("quot   R%d  R%d  R%d", register1, register2, register3);
    }
    else if (opcode == MOD) { /*Prints 3 registers*/
      printf("mod    R%d  R%d  R%d", register1, register2, register3);
    }
    else if (opcode == AND) { /*Prints 3 registers*/
      printf("and    R%d  R%d  R%d", register1, register2, register3);
    }
    else if (opcode == OR) { /*Prints 3 registers*/
      printf("or     R%d  R%d  R%d", register1, register2, register3);
    }
    else if (opcode == NOT) { /*Prints 2 registers*/
      printf("not    R%d  R%d", register1, register2);
    }
    else if (opcode == BR) { /*Prints 1 register and the memory address*/
      printf("br     R%d  %05d", register1, mem_address);
    }
    else if (opcode == READ) { /*Prints 1 register*/
      printf("read   R%d", register1);
    }
    else if (opcode == WRT) { /*Prints 1 register*/
      printf("wrt    R%d", register1);
    }
    else if (opcode == MOVE) { /*Prints 2 registers*/
      printf("move   R%d  R%d", register1, register2);
    }
    else if (opcode == LW) { /*Prints 1 register and the memory address*/
      printf("lw     R%d  %05d", register1, mem_address);
    }
    else if (opcode == SW) { /*Prints 1 register and the memory address*/
      printf("sw     R%d  %05d", register1, mem_address);
    }
    else if (opcode == LI) { /*Prints 1 register and immediate operand*/
      printf("li     R%d  %d", register1, mem_address);
    }
    return 1;
  } else {
    return 0;
  }
}

/*Prints each instruction in program[] preceded by the first 4 digits of its
  memory address, then it prints the data portion of the program, which consists 
  of memory addresses preceded by the element's memory address*/
int disassemble(const Word program[], unsigned int instr_num,
                unsigned int data_num) {
  unsigned int i= 0;

  if (program != NULL && instr_num > 0 && data_num + instr_num <=3072) {
    /*Prints VALID instructions*/
    for (i = 0; i < instr_num; i++) {
      if (is_valid_instruction(program[i])) {
        printf("%04x: ", (unsigned int)(i * sizeof(program[i])));
        print_instruction(program[i]);
        printf("\n");
      } else {
        return 0;
      }
    }
    if (data_num > 0) {
      /*Prints data segnment*/
      for (i = instr_num; i < instr_num + data_num; i++) {
        printf("%04x: ", (unsigned int)(i * sizeof(program[i])));
        printf("%08x\n", program[i]);
      }
    }
    return 1;
  }
  return 0;
}

/*Verifies validity of word instruction parameter*/
int is_valid_instruction(Word word) {
  unsigned int mask = 0, mem_address= 0, opcode= 0, register1= 0, register2= 0,
  register3= 0;

  mask = 15; /*This sets leftmost 4 bits to 1*/
  opcode = word>>28 & mask; /*Isolates the opcode*/

  mask = 524287; /*Makes 19 bits = 1 */
  mem_address = word>>9 & mask; /*Isolates value of memory address*/

  mask = 7;
  register1 = word>>6 & mask; /*Isolates value of the first register*/
  register2 = word>>3 & mask; /*Isolates value of second register*/
  register3 = word & mask; /*Isolates value of third register*/

  /*Verifies that opcode is valid*/
  if (opcode >=PLUS && opcode <=LI && (register1 >=0 && register1 < 7)) {
    /*Verifies that USED register operands are valid*/
    if (((opcode >=PLUS && opcode < NOT) && (register2 >=0 && register2 < 7) &&
      (register3 >=0 && register3 < 7)) || ((opcode == NOT || opcode == MOVE)
      && (register2 >=0 && register2 < 7)) || ((opcode == BR || opcode == READ
      || opcode == WRT || opcode == LW || opcode == SW || opcode == LI))) {

      /**Determines if memory address is used by filtering out for the opcodes
        which use a memory address**/
      if (opcode == BR || opcode == LW || opcode == SW) {
        /***if the memory address is NOT divisible by 4 and/or is GREATER
            than the maximum 12287, then 0 must be returned***/
        if (mem_address > 12287 || mem_address % 4 != 0) {
          return 0;
        }
      }

      if (opcode == LI) {
      /*Returns 0 if immediate value is greater than the maximum able to be
        stored within 18 bits*/
        if (mem_address > 524287) {
          return 0;
        }
      }
      /**Verifies that instructions that modify memory do not use register 0 or
         register 6 as the first register argument**/
      if (opcode != BR && opcode != WRT && opcode != SW) {
        /***If first register operand is R0 or R6, 0 must be returned***/
        if (register1 == 0 || register1 == 6) {
          return 0;
        }
      }
    } else {
      return 0;
    }
    return 1;
  }
  return 0;
}

/*This function shifts the memory address of each instruction that uses
  a memory address in program[] by the value in the offset parameter. Regardless
  of the instruction, all valid instructions will be copied to the array
  relocated_program*/
int relocate(const Word program[], unsigned int instr_num,
             unsigned int data_num, int offset, Word relocated_program[],
             unsigned short *const instrs_changed) {
  int i= 0;
  unsigned int mask= 15, mem_address= 0, opcode= 0;

  if (program == NULL || relocated_program == NULL || instr_num < 1 || offset
      % 4 != 0 || instrs_changed == NULL || data_num + instr_num > 3072) {
    return 0;
  } else {
    for (i= 0; i < instr_num + data_num; i++) {
      if (is_valid_instruction(program[i])) {
        /*Isolates opcode to verify if instruction uses memory address*/
        opcode = program[i]>>28 & mask;

        /*Determines if instruction uses the memory address space of the word*/
        if (opcode == BR || (opcode >= LW && opcode <=LI)) {
          mask = 524287; /*Sets 19 bits = 1*/
          mem_address = program[i]>>9 & mask; /*Isolates memory address*/

          /*If the resulting modified memory address is invalid*/
          if (mem_address + offset > 12287 || (int)(mem_address + offset) < 0) {
            return 0;
          }
          relocated_program[i] = program[i];
          mem_address += offset;
          relocated_program[i] &= 4026532351;
          /*^Resets the 19 bit memory address portion of the word*/
          relocated_program[i] |= mem_address<<9;/*Inserts new memory address*/
          (*instrs_changed)++;
        } else {
          relocated_program[i] = program[i];
        }
      } else { /*Returns 0 if any element in program is invalid*/
        return 0;
      }
    }
    return 1;
  }
}
