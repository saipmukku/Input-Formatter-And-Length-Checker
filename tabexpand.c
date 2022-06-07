/* 
   TerpConnect login ID: saipmukk
   University ID Number: 118058573
   Discussion Section: 0102
*/

/*
  I pledge on my honor that I have not given or received
  unauthorized assistance on this assignment/examination.
*/

/*
  Block comment: This program is very similar to the one that checks the 
  length of each line in a file, except whenever it reads a tab character,
  it increases the number of spaces in the output until it comes across 
  the next tab stop, essentially producing an output that would be exactly 
  how it would come out in a printer, for example, or a text editor like emacs.
*/

#include <stdio.h>

int main(void){

  /*
    This loop runs until the end of the input, and it declares multiple 
    variables that include an array of chars that holds the characters 
    of every line, a char type variable that holds the current character 
    being looked at, and other indicator and pointer variables.
  */

  while(!feof(stdin)){
    
    char letters[999];
    char next_character;
    int tab_stop = 0;
    int read_in = 0;
    int size = 0;
    int end_line = 1;

    /*
      Like the other program, this loop reads through one line at a 
      time, and adds every character to the char array that was 
      initialized in the beginning of the block.
    */

    while(end_line){

      scanf("%c", &next_character);

      if(next_character == '\n'){
	
	letters[read_in] = next_character;
        end_line = 0;

      } else {

	letters[read_in] = next_character;
	size++;
	
      }

      read_in++;

    }

    /*
      From here on out, the program redeclares these two variables for use 
      again in another loop. The loop then goes through every letter, and 
      if it is not a tab character, it prints it out to the output. It also
      increases the "tab_output" variable by 1 unless it is 8, in which case 
      it sets it back to 0. This effectively makes it so that when the loop 
      that produces spaces based on the "tab_stop" variable runs, it knows how 
      many times a space should be produced. Whenever a tab character is read
      by the scanner, it produces a space and increases the "tab_stop" variable
      until it is 8, no matter what the variable value was to begin with. 
    */
    
    end_line = 1;
    read_in = 0;

    while(end_line){

      next_character = letters[read_in];
      read_in++;

      if(next_character == '\t'){

	while(tab_stop != 8){

	  printf(" ");
	  tab_stop++;

	}

	tab_stop = 0;

      } else if(next_character == '\n'){
	
        end_line = 0;

      } else {

	printf("%c", next_character);

	if(tab_stop == 8){

	  tab_stop = 0;

	} else {
	
	  tab_stop++;
	
	}

      }

    }

    if(!feof(stdin)) printf("\n");

  }

  return 0;

}
