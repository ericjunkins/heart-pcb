/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define HIGH_MASK  0xF0
#define LOW_MASK   0x0F

#define D1_MASK    0x01
#define D2_MASK    0x02
#define D3_MASK    0x04
#define D4_MASK    0x08

char *stringToBinary(char *s)
{
  if (s == NULL) {
    // NULL might be 0 but you cannot be sure about it
    return NULL;
  }
  // get length of string without NUL
  size_t slen = strlen(s);
  // we cannot do that here, why?
  // if(slen == 0){ return s;}
  errno = 0;
  // allocate "slen" (number of characters in string without NUL)
  // times the number of bits in a "char" plus one byte for the NUL
  // at the end of the return value
  char *binary = malloc(slen * CHAR_BIT + 1);
  if(binary == NULL){
     fprintf(stderr,"malloc has failed in stringToBinary(%s): %s\n",s, strerror(errno));
     return NULL;
  }
  // finally we can put our shortcut from above here
  
  if (slen == 0) {
    *binary = '\0';
    return binary;
  }
  char *ptr;
  // keep an eye on the beginning
  char *start = binary;
  int i;

  // loop over the input-characters
  for (ptr = s; *ptr != '\0'; ptr++) {
    /* perform bitwise AND for every bit of the character */
    // loop over the input-character bits
    for (i = CHAR_BIT - 1; i >= 0; i--, binary++) {
      *binary = (*ptr & 1 << i) ? '1' : '0';
    }
  }
  // finalize return value
  *binary = '\0';
  // reset pointer to beginning
  binary = start;
  return binary;
}

int* strToBinArray(char * s, int *arr){
    char *ptr;
    int i = 0;
    
    for(ptr = s; *ptr != '\0'; ptr++){
        int temp_high = *ptr & HIGH_MASK;
        int temp_low  = *ptr & LOW_MASK;
        arr[i]   = temp_low;
        arr[i+1] = temp_high >> 4;
        i+=2;
    }
    return arr;
}

void flipLEDs(int *arr){
    int led1;
    int led2; 
    int led3;
    int led4;
    
    for(int j =0; j<sizeof(arr); j++){
        led1 = (arr[j] & D1_MASK) >> 0;
        led2 = (arr[j] & D2_MASK) >> 1;
        led3 = (arr[j] & D3_MASK) >> 2;
        led4 = (arr[j] & D4_MASK) >> 3;
        printf("LED output is: %d, %d, %d, %d \n", led1,led2,led3,led4);
    }
    
}

int main(int argc, char **argv)
{
  char *output;
  char *message = "Iloveyou";
  size_t slen = strlen(message);
  int bitArr[slen*2];
 
  printf("%s\n", stringToBinary(message));
  
  int* led = strToBinArray(message, bitArr);
  flipLEDs(led); 

  exit(EXIT_SUCCESS);
}