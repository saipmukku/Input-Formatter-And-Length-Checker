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
  Block comment: This program declares one instance of an array that holds
  input from each line of a file, and determines whether the entire file
  meets the standard of only 80 characters in each line. It counts tabs as
  one character, and knows when to go to the next line whenever it scans a 
  '\n' character.
*/

#include <stdio.h>

int main(void) {

  char letters[999];

  /* 
     This loop ends once the program reaches the end of the file. It declares
     a char variable that holds the current character that is being read from
     the file, and performs certain actions based on the character that was just
     read. The other variables are integers that act as pointers and indicators.
  */

  while(!feof(stdin)){
    
    /* 
       These variables are the ones mentioned in the previous comment. The 
       variable "end_line" indicates when the input has reached a newline
       character, and it stops the first while loop. The "read_in" variable 
       is a pointer variable which points to what the next in the array is 
       to be used next. The "arr_counter" variable is used later in the 
       program for the same purpose. The "size" variable just keeps track
       of the size of the current line that is being looked at. Like mentioned 
       before, '\t' only counts as one character towards the size."
    */

    char next_character;
    int end_line = 1;
    int read_in = 0;
    int arr_counter = 0;
    int size = 0;

    while(end_line){

      /*
	This loop populates an array of chars with the characters of one line 
	of the input at a time. If the character that was just read was a newline 
	character, then it adds that to the array, and then changes the value of 
	a variable that ends the while loop. If that character that was just read
	was not a newline character, then that character is added to the char array
	at the index indicated by "read_in", and the size variable is incremented. 
	No matter what that last character was, the "read_in" variable is 
	incremented, moving the pointer forward through the array.
      */

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
      This if statement block produces the proper format for output, and 
      then it iterates through the current array after the first 
      seven characters of the output are produced, rewriting the array
      stored in the char array (this is done with a while loop).
    */

    if(!feof(stdin)){

      if(size > 80) printf("X");

      else printf(" ");

      printf(" ");
      printf("%3d", size);
      printf(": ");
      
      while(size != arr_counter){
      
	if(letters[arr_counter] == '\n'){

	  printf("\n");

	} else {

	  printf("%c", letters[arr_counter]);
	  arr_counter++;

	}

      }

      printf("\n");

    }

  }

  return 0;

}
