/* 
Geraldo Martinez
gm979351
Friday 1:40
*/

#include <stdio.h>
#define array_size 31

/* Reads a decimal integer from the user and prints out it's value in binary */

int main(void) {

  int x;
  int a[array_size];
  int numbers=0;
  int module;
  int counter;
  int numberOfOnes;
  int cLength=0;
  int mLength=0;

  /* Inputs the user for the decimal */
  printf("Enter a decimal integer: ");
  fflush(stdout);
  scanf("%d", &x);

  /*Special Case for negative integers.*/
  if (x < 0){
    printf("Input value is negative.\n");
    fflush(stdout);
  }

  /* Special case for when user inputs 0. */
  if (x == 0){
    printf("Binary representation = %d\n", x);
    fflush(stdout);
    printf("No. of 1's in the binary representation = %d\n", x);
    fflush(stdout);
    printf("Maximum block length = %d\n", x);
    fflush(stdout); 
  }

  /* Converts the decimal to binary */

  if(x>0){
   
    /* Loops through as many times needed to have remainder equal to 0 */ 
    for(counter=0;x>=1;counter++){
      module=x%2;
      if((x%2)==1){
	numberOfOnes++;
      }
      x=x/2;
      numbers++;
      a[counter]=module;


      /* Checks for the max block length by using two variables */
      if(a[counter]==1){
	cLength++;
      }
      if(a[counter]==0){
	cLength=0;
      }
      if(cLength > mLength){
	mLength=cLength;

      }
    }

    printf("\nBinary representation = ");

    /* Prints out the binary representation */
    for(counter=(numbers-1); counter>=0; counter--){
      printf("%d", a[counter]);
      fflush(stdout);
    }

    printf("\nNo. of 1's in the binary representation = %d\n", numberOfOnes);
    fflush(stdout);

    printf("Maximum block length = %d\n", mLength);
    fflush(stdout);
 
  }
  return 0;
} /* End of main. */

