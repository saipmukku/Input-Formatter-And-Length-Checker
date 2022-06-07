/* 
  TerpConnect login ID: saipmukk
  University ID Number: 118058573
  Discussion Section: 0102

  I pledge on my honor that I have not given or received
  unauthorized assistance on this assignment/examination.

  Block comment: This file contains all the code for the
  prototypes in the header file "machine.h", as well as the 
  struct in "nelovo-datastructure.h". It defines the methods 
  "print_instruction", "disassemble", "is_valid", "check_branches",
  "load_program", "get_register", "get_memory", and "run_program", 
  which operate in various ways on instructions that are read by a 
  Nelovo machine.
*/

#include <stdio.h>
#include "machine.h"

/*
  The "print_instruction" method takes a 4 byte instruction as a parameter, and
  bit-shifting and bit-masking tactics to interpret the instruction as it would
  be read by the Nelovo machine. It then prints out the opcode, registers used,
  and, if applicable, the address/immediate operand.
*/

unsigned short print_instruction(Mach_word instr) {

  /*
    These are variable declarations that do the proper bit operations on 
    the instruction to extract the necessary data. These variables are then 
    interpreted by the rest of the function to print out the proper output.
  */

  int op = instr >> 26;
  int reg_1 = (instr >> 22) & 15;
  int reg_2 = (instr >> 18) & 15;
  int reg_3 = (instr >> 14) & 15;
  int add_imm = instr & 16383;

  /*
    This statement returns the value 0 if the instruction 
    is not a valid instruction, calling "is_valid".
  */

  if (!(is_valid(instr))) return 0;

  /*
    The next statements determine what to print based on the opcode, which is 
    denoted by the "op" variable. It is assumed that "op" will not exceed 22 
    since this point of the function can only be reached if the instruction is
    a valid instruction. For example, if the "op" variable is found out to be 
    5 after the bit operations, the opcode "rem" would be printed, alongside 
    the registers that were denoted in the instruction.
  */

  if (op == 0) {

    printf("halt");

  } else if (op == 1) {

    printf("add R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 2) {

    printf("sub R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 3) {

    printf("mul R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 4) {

    printf("div R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 5) {

    printf("rem R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 6) {

    printf("neg R%d R%d", reg_1, reg_2);

  } else if (op == 7) {

    printf("and R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 8) {

    printf("or R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 9) {

    printf("not R%d R%d", reg_1, reg_2);

  } else if (op == 10) {

    printf("eql R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 11) {

    printf("neq R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 12) {

    printf("lt R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 13) {

    printf("gt R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 14) {

    printf("le R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 15) {

    printf("ge R%d R%d R%d", reg_1, reg_2, reg_3);

  } else if (op == 16) {

    printf("test R%d %05d", reg_1, add_imm);

  } else if (op == 17) {

    printf("move R%d R%d", reg_1, reg_2);

  } else if (op == 18) {

    printf("li R%d %d", reg_1, add_imm);

  } else if (op == 19) {

    printf("lw R%d %05d", reg_1, add_imm);

  } else if (op == 20) {

    printf("sw R%d %05d", reg_1, add_imm);

  } else if (op == 21) {

    printf("read R%d", reg_1);

  } else if (op == 22) {

    printf("prt R%d", reg_1);

  }

  /*
    1 is returned after the function is finished 
    reading and interpreting the instruction.
  */

  return 1;

}

/*
  The disassemble function takes in a structure that contains instructions
  for the Nelovo in an array of unsigned integers, with the typedef 
  "Mach_word", as well as an unsigned short named "max_addr", which 
  indicates the memory address of the last instruction in the structure's 
  instructions array, telling the function when to stop reading from
  the "program" array. When the instructions are read, the function reads
  them one by one from the array, outputs the memory address of the
  instruction in hexadecimal, then prints out the instruction in readable
  format. If an invalid instruction is read, 0 is returned and nothing
  else is printed.
*/

unsigned short disassemble(Nelovo machine, unsigned short max_addr) {

  /*
    The next two statements declare a variable that denotes the current 
    element in "program", and then return 0 if the "max_addr" is greater 
    than the greatest amount of bytes that the Nelovo can hold.
  */

  int current_mem = 0;

  if (max_addr > 16380 && max_addr < 0) return 0;

  /*
    This while loop iterates through the structure's instructions array,
    treating each instruction as 4 bytes, and then stopping once the 
    memory address of the last instruction is equal to the "max_addr" 
    value. The while loop decreases the value of "current_mem" by one 
    before multiplying it by four and comparing it to the "max_addr" 
    value because it is incremented within the while loop itself, which 
    makes sure that the while loop stops at the right time.
  */

  while (((current_mem - 1) * 4) != max_addr) {

    /*
      If the instruction currently being looked at is not valid, then the while
      loop stops and 0 is returned. This also makes it so that every instruction
      before the first invalid instruction is processed before 0 is returned and
      the function is "terminated".
    */

    if (!(is_valid(machine.instructions[current_mem]))) return 0;

/*
      This part of the while loop prints out the current memory address of the
      instruction being looked at in hexadecimal, then it prints out the
      instruction in the proper format by invoking the "print_instruction"
      method. It then prints a newline character, and then increments the
      "current_mem" variable. This makes it so that the next instruction is
      primed to be processed by the method, and that the proper comparison
      can be made within the while loop condition.
    */

    printf("%04x: ", (current_mem * 4));
    print_instruction(machine.instructions[current_mem]);
    printf("\n");
    current_mem++;

  }

  /*
    1 is returned if this point in the program is reached. This also means that
    every instruction read from the "program" array was valid.
  */

  return 1;

}

/*
  This function takes a Nelovo instruction as an argument, and then based on
  the format of that instruction, will return 0 is the instruction was
  invalid, or will return 1 is the instruction was valid.
*/

unsigned short is_valid(Mach_word word) {

  int op = word >> 26;
  int reg_1 = (word >> 22) & 15;
  int reg_2 = (word >> 18) & 15;
  int reg_3 = (word >> 14) & 15;
  int add_imm = word & 16383;

  /*
    This long if statement checks to see if all the proper conditions for a
    valid instruction is met. It makes sure the opcode value is between
    0 and 22, and then it makes sure that each register is between 0 and
    13, since each Nelovo machine has 14 registers. After checking for
    these, it makes sure that if the instruction has an address associated
    with it, that this address is divisible by 4, since all instructions
    are 4 bytes and memory addresses must denote where an instruction
    starts. It also makes sure that certain opcodes do not have register
    13 as its first register, since that would not make sense based on the
    nature of register 13.
  */

  if ((op > 22 || op < 0) || (reg_1 < 0 || reg_1 > 13) || 
     (reg_2 < 0 || reg_2 > 13) || (reg_3 < 0 || reg_3 > 13) || 
     ((op == 16 || op == 19 || op == 20) && (add_imm % 4 != 0)) 
     || ((op != 16 && op != 20 && op != 22) && (reg_1 == 13))
     || ((op != 18 && op != 19 && op != 21) && (reg_1 == 13))) {

    /*
      If the above condition is met, 0 is returned, indicating that
      instruction parameter is invalid.
    */

    return 0;

  }

  /*
    If the above if statement was not called, then the instruction was
    valid, and 1 is returned.
  */

  return 1;

}

/*
  The "check_branches" function also takes in a structure as a pointer, as
  well as a "max_addr" variable that indicates the memory address of the last
  instruction in the "program" array. It also contains another pointer parameter
  that points to a variable that will hold the first invalid instruction read 
  by the function. This function looks for "test" instructions and determines 
  the validity of the address/immediate operand.
*/

short check_branches(Nelovo *const machine, unsigned short 
		     max_addr, unsigned short *const invalid_instr) {
 
  /*
    Three variables are declared here, which represent the opcode and the
    address/immediate operand. The other variable declared is just used
    to iterate through the "program" array.
  */

  int op, add_imm, current_mem = 0;

  /*
    If "max_addr" is invalid, as in greater than 16380, or the pointers 
    are NULL, then -1 is returned.
  */

  if (max_addr > 16380 || machine == NULL || invalid_instr == NULL) return -1;

  /*
    This while loop is similar to the while loop in the disassemble function
    in that it reads through instructions in the structure's instructions 
    array until the "max_addr" value is reached 
    (doing all the proper calculations).
  */

  while ((current_mem * 4) != max_addr) {

    /*
      These variables using bit operations to determine the proper opcode
      and address/immediate operand of the current instruction being read
    */

    op = machine->instructions[current_mem] >> 26;
    add_imm = machine->instructions[current_mem] & 16383;

    /*
      If the "op" variable is 16 after the bit operation, that means that
      the instruction being read is a "test" instruction, and the next 
      step of evaluating the instructions in the structure array should
      be carried out.
    */

    if (op == 16)

      /*
	If the "add_imm" value of the "test" instruction is not divisible 
	by 4, or if the memory address of the "test" instruction is 
	greater than the "max_addr" value, then the memory address of the
	instruction is returned (according to the guidelines for the
	project). 
      */

      if ((add_imm % 4 != 0) || ((current_mem * 4) > max_addr)) {

	*invalid_instr = (current_mem * 4);
	return 0;

      }

    /*
      This just increments the value of "current_mem", iterating through
      the array.
    */

    current_mem++;

  }
  
  /*
    If all the instructions in the structure's instructions array 
    are read and each "test" instruction has a valid address/immediate 
    operand value, then 1 is returned, indicating the above.
  */

  return 1;

}

/*
  This function takes in a Nelovo structure that contains two fields, one
  that contains the values of the registers, and one that contains all the
  values in the 4096 memory locations (16384 actual byte locations, but
  the 4096 words that the storage can actually hold.), and it copies all of
  the instructions from the "program" array into the memory field for
  instructions in the Nelovo structure. The "num_instrs" is just a counter
  variable that tells the function how many times to iterate through the
  array, since C does not have a method of determining the size of an array.
*/

unsigned short load_program(Nelovo *const machine, 
			    const Mach_word program[], unsigned short num_instrs) {

  /*
    This integer denotes both what instruction is being copied in the "program"
    array, as well as where to put this instruction in the Nelovo structure's
    "instructions" field.
  */

  int current_instr = 0;

  /*
    This if statement determines if the parameters of the method are invalid.
  */
  
  if(machine == NULL || program == NULL || num_instrs > 4096) return 0;

  /*
    This while loop iterates through the "program" array based on the value of
    "num_instrs" variable.
  */

  while(current_instr < num_instrs) {

    /*
      These statements access the instruction in the spot of the
      array determined by the "current_instr" variable, and copies 
      it into the same spot in the "instructions" array in the Nelovo 
      structure. It then increments the "current_instr" variable by one.
    */

    machine->instructions[current_instr] = program[current_instr];
    current_instr++;

  }

  /*
    If the parameters were not invalid, and the function runs without any
    error, 1 is returned to indicate that the function ran successfully.
  */

  return 1;

}

/*
  This method puts the value of the specified register into the variable 
  that is being pointed to by the result parameter.
*/

unsigned short get_register(Nelovo machine, 
			    unsigned short which_register, Mach_word *const result) {

  /*
    This if statement returns 0 if any of the parameters are invalid.
  */

  if(result == NULL || which_register > 13 || which_register < 0) return 0;

  /*
    This statement sets the variable that "result" is pointing to, to the value
    in the specified register in the array field of the Nelovo structure.
  */

  *result = machine.registers[which_register];

  /*
    This method returns 1 if the parameters were valid and the rest of the
    function ran without any error.
  */

  return 1;

}

/*
  This method puts the value in the specified memory address into the variable 
  that is being pointed to by the result parameter.
*/

unsigned short get_memory(Nelovo machine, 
			  unsigned short which_memory_addr, Mach_word *const result) {

  /*
    This if statement returns 0 if any of the parameters are invalid.
  */

  if(result == NULL || which_memory_addr > 16380 || which_memory_addr % 4 != 0)
    
    return 0;

  /*
    This statement sets the variable that "result" is pointing to, to the
    value in the specified memory address in the array field of the Nelovo
    structure.
  */

  *result = machine.instructions[which_memory_addr / 4];

  /*
    This method returns 1 if the parameters were valid and the rest of the
    function ran without any error.
  */

  return 1;

}

/*
  This method takes in multiple parameters: a Nelovo structure, the number
  of instructions to be read, the number of instructions executed, a pointer
  to a variable that will hold the first invalid instruction read by the 
  function, and a variable that helps with debugging the function. This 
  function takes the instructions that are being stored in the Nelovo structure
  and executes them sequentially (unless a special instruction tells the 
  function to do otherwise.). It modifies the registers in the Nelovo structure,
  as well as the actual values of the memory as represented by the array in 
  the Nelovo structure.
*/

Status run_program(Nelovo *const machine, unsigned int max_instrs, 
		   unsigned short *const num_instrs_executed, 
		   unsigned short *const invalid_instr, unsigned short trace_flag) {

  /*
    The short variable is used as a counter for a for loop that initializes
    all of the registers' values to 0. The "Mach_word" variable is an
    unsigned integer that tells the function what current instruction is
    being looked at by the functino.
  */

  short reg_initialize = 0;
  Mach_word current_instr;

  /*
    This if statement checks to see if either of the pointer parameters
    are NULL, in which case it returns the Status enum value, "ERROR".
  */

  if(num_instrs_executed == NULL || invalid_instr == NULL) return ERROR;

  /*
    This for loop initializes all of the registers' values to 0 using
    the "reg_initialize" short variable.
  */

  for(reg_initialize = 0; reg_initialize < 14; reg_initialize++)

    machine->registers[reg_initialize] = 0;

  /*
    This statement sets the "current_instr" variable to the value of
    the thirteenth register, which is a variable that tells the
    function what instruction to be looking at. This will always be
    0 at this point in the function, but it is done for consistency
    sake, since a very similar statement is in the below while loop.
  */

  current_instr = machine->registers[13];

  /*
    This while loop iterates through the instructions in the Nelovo structure
    based on the "max_instrs" variable.
  */

  while(current_instr < max_instrs){

    /*
      These are variables that do the proper bit-shifting and bit-masking
      on the instructions in order to extract the proper data and perform
      the correct instructions on the right registers, altering the right
      fields.
    */

    int current_instr = machine->instructions[machine->registers[13]];
    int op = current_instr >> 26;
    int reg_1 = (current_instr >> 22) & 15;
    int reg_2 = (current_instr >> 18) & 15;
    int reg_3 = (current_instr >> 14) & 15;
    int add_imm = current_instr & 16383;
    
    /*
      This if statement checks to see if the instruction that is currently
      being looked at is valid or not. If it is not, it changes the value
      of the variable that "invalid_instr" is pointing to, and then returns
      "ERROR" from the Status enum.
    */

    if(!(is_valid(current_instr))) {

      *invalid_instr = current_instr;
      return ERROR;

    }

    /*
      These next if statements perform the proper operations based on the
      opcodes determined by the bit-shifting above.
    */

    if (op == 0) {

      /*
	This halts the function.
      */

      return HALTED;

    } else if (op == 1) {

      /*
	Performs addition using register 2 and register 3, 
	putting the result into register 1.
      */

      machine->registers[reg_1] = machine->registers[reg_2] 
	+ machine->registers[reg_3];

    } else if (op == 2) {

      /*
	Performs subtraction using register 2 and register 3, 
	putting the result into register 1.
      */

      machine->registers[reg_1] = machine->registers[reg_2] 
	- machine->registers[reg_3];

    } else if (op == 3) {

      /*
	Performs multiplication using register 2 and register 3, 
	putting the result into register 1.
      */

      machine->registers[reg_1] = machine->registers[reg_2] 
	* machine->registers[reg_3];

    } else if (op == 4) {

      /*
	Performs division using register 2 and 
	register 3, putting the result into register 1.
	If the value in register 3 is 0, an ERROR is
	returned, since division by 0 is not possible.
      */

      if(machine->registers[reg_3] == 0) return ERROR;

      machine->registers[reg_1] = machine->registers[reg_2] 
	/ machine->registers[reg_3];

    } else if (op == 5) {

      /*
	Performs modulus division using register 2 and 
	register 3, putting the result into register 1.
	If the value in register 3 is 0, an ERROR is
	returned, since division by 0 is not possible.
      */

      if(machine->registers[reg_3] == 0) return ERROR;

      machine->registers[reg_1] = machine->registers[reg_2] 
	% machine->registers[reg_3];

    } else if (op == 6) {

      /*
        Puts the value in register 2 multiplied by -1 into
	register 1.
      */

      machine->registers[reg_1] = -(machine->registers[reg_2]); 
    
    } else if (op == 7) {

      /*
        Performs a logical "and" operation on the values in
	register 2 and register 3.
      */
      
      machine->registers[reg_1] = machine->registers[reg_2] 
	&& machine->registers[reg_3];

    } else if (op == 8) {

      /*
        Performs a logical "or" operation on the values in
	register 2 and register 3.
      */

      machine->registers[reg_1] = machine->registers[reg_2] 
	|| machine->registers[reg_3];

    } else if (op == 9) {

      /*
        Performs a logical "negation" operation on the values in
	register 2 and register 3.
      */

      machine->registers[reg_1] = !(machine->registers[reg_2]);

    } else if (op == 10) {

      /*
        Performs a logical "equals" operation on the values in
	register 2 and register 3.
      */

      machine->registers[reg_1] = machine->registers[reg_2] 
	== machine->registers[reg_3];
      
    } else if (op == 11) {

      /*
        Performs a logical "not equals" operation on the values in
	register 2 and register 3.
      */

      machine->registers[reg_1] = machine->registers[reg_2] 
	!= machine->registers[reg_3];

    } else if (op == 12) {

      /*
        Performs a logical "less than" operation on the 
	values in register 2 and register 3.
      */

      machine->registers[reg_1] = machine->registers[reg_2] 
	< machine->registers[reg_3];

    } else if (op == 13) {

      /*
        Performs a logical "greater than" operation on the 
	values in register 2 and register 3.
      */

      machine->registers[reg_1] = machine->registers[reg_2] 
	> machine->registers[reg_3];

    } else if (op == 14) {

      /*
        Performs a logical "less than or equal to" operation
	on the values in register 2 and register 3.
      */

      machine->registers[reg_1] = machine->registers[reg_2] 
	<= machine->registers[reg_3];

    } else if (op == 15) {

      /*
        Performs a logical "greater than or equal to" operation
	on the values in register 2 and register 3.
      */

      machine->registers[reg_1] = machine->registers[reg_2] 
	>= machine->registers[reg_3];

    } else if (op == 16) {

      /*
        This operation is done by changing the value of the
	program counter register.
      */

      if(machine->registers[reg_1] != 0) 
	
	machine->registers[13] = (add_imm / 4);

    } else if (op == 17) {

      /*
	This operation puts the value of 
	register 2 inside of register 1.
      */

      machine->registers[reg_1] = machine->registers[reg_2];

    } else if (op == 18) {

      /*
	This operation changes the value of register 1 to the
	value denoted by the last 14 bits of the instruction.
      */

      machine->registers[reg_1] = (add_imm);

    } else if (op == 19) {

      /*
	This operation sets the value of register 1 to the value
	inside of the memory space in the address denoted by the
	last 14 bits of the original instruction.
      */

      machine->registers[reg_1] = machine->instructions[(add_imm / 4)];

    } else if (op == 20) {

      /*
	This operation sets the value in the memory space inside
	Nelovo structure to the value in register 1.
      */

      machine->instructions[(add_imm / 4)] = machine->registers[reg_1];

    } else if (op == 21) {

      /*
	This operation reads from standard input and puts the
	value in register 1.
      */

      int input;
      scanf("%d", &input);
      machine->instructions[reg_1] = input;

    } else if (op == 22) {

      /*
	This operation prints out the value in register 1
	to standard output.
      */

      printf("\n%d", machine->instructions[reg_1]);

    }

    /*
      This if statement increments the value of the program counter
      if the operation is not "test".
    */

    if(op != 16) ((machine->registers[13])++);

    /*
      These next two statements just increment the proper variables,
      allowing the while loop to progress to the next instruction,
      and increasing the value of the variable being pointed to by
      "num_instrs_executed" pointer by 1.
    */

    (*num_instrs_executed)++;
    current_instr++;

  }

  /*
    If this point of the function is reached, the value "RUNNING"
    from the Status enum is returned by the function.
  */

  return RUNNING;

}
