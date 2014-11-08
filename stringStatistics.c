/*
Geraldo Martinez
gm979351
Friday 1_40
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Max. number of characters for each word in the word array. */
#define array_size 16

/* Prototypes of all of the functions used in this program. */
int vowel_count(char word[]);
int three_vowels(char word[]);
int is_palindrome(char word[]);

/* The main function. */
int main(void){

  char word[array_size]; /* Stores the word inputted by the user. */
  float cWords=0; /* Keeps track of the number of words in the input. */
  float cChars=0; /* Keeps track of the total number of characters in the input. */ 
  float averageWordLength; /* Holds the value of the average length of each word in the input. */
  float averageVowels; /* Holds the value of the average number of vowels per word in the input. */
  int palindromes; /* Keeps track of the number of palindromes in the input. */
  float vowelCount; /* Keeps track of the number of vowels in one word of the input. */
  int threeVowelsCounter; /* Keeps track of the number of words that have atleast three vowels in the input. */
  int word_atleast_ten; /* Keeps track of the number of words whose length is atleast 10 but no more than 15 chars. */
  int wordLength; /* Holds the number of chars for each word. */
  int i= 0; /* Counter for the for loop to remove special characters. */

  printf("Please enter the string: \n");
  fflush(stdout);

  /* Inputs the user for a series of chars, and reaches EOF when word is equal to something other than one. */
  while(scanf("%s", word)==1){


    /* Loops around current word input and checks if it has a punctuation marks, if it does it removes that char. */
   
    for(i=0; i<word[i]; i++){
      if((word[i]== '.') || (word[i]== ',') || (word[i]== ';') || (word[i]=='?') || (word[i]=='!')){
	word[strlen(word)-1]=0;
      }
    }

    cWords++; /* Increments the number of words for each time the loop runs. */

    wordLength = strlen(word); /* Finds the number of chars of the current word. */

    /* Checks to see if the current word has at least 10 chars but no more than 15, if it does it tracks it in the word_atleast_ten variable. */
    if ((wordLength >= 10) && (wordLength <= 15)){
      word_atleast_ten++;
    }

    cChars+=strlen(word); /* Calculates the total number of chars in the input. */
    palindromes+= is_palindrome(word); /* Calculates the total number of palindromes in the input/ */
    vowelCount+= vowel_count(word); /* Calculates the total number of vowels in the input. */
    threeVowelsCounter += three_vowels(word);/* Calculates the total number of words with more than three vowels in the input. */
  }


  /* Computations. */

  averageWordLength = cChars/cWords; /* Finds the average length of each word in the input. */
  averageVowels = vowelCount/cWords; /* Finds the average vowels per word in the input. */

  /* Prints all of the statistical information needed for the input of words. */

  printf("Average length of the words in the input is %f\n",averageWordLength);
  fflush(stdout);
  printf("Average number of vowels in a word is %f\n", averageVowels);
  fflush(stdout);
  printf("Number of words in the input with atleast three vowels is %d\n", threeVowelsCounter);
  fflush(stdout);
  printf("Number of words in the input in which are palindromes: %d\n", palindromes);
  fflush(stdout);
  printf("Number of words in the input whose length is atleast ten but less than sixteen chars long: %d\n", word_atleast_ten);
  fflush(stdout); 

  return 0;
}

/* Code for the vowel_count function. */

int vowel_count (char word[]){

  /* The input parameter word represents an array of chars. This function simply returns the number of vowels in the word inputted by the user. */

  int vowelCount = 0; /* Keeps track of the number of vowels in the word. */
  int i=0; /* Counter in the While Loop. */

  /* Loop that goes through each char in the word and checks if it is a vowel, either capital or lower case. */
  while(word[i]!='\0'){
    if((word[i]=='a') || (word[i]=='A') || (word[i]=='e') || (word[i]=='E')
       || (word[i]=='i') || (word[i]=='I') || (word[i]=='o') || (word[i]=='O')
       || (word[i]=='u') || (word[i]=='U')) {
      vowelCount++;
    }
    i++;
  }
  return(vowelCount); /* Returns the number of vowels in the word. */
}

/* Code for the three_vowels function.*/

int three_vowels (char word[]){

  /* The input parameter word represents an array of chars. This function simply returns the number of words in an input of words for which there are more than three vowels in a word */

  int vowelCounter; /* Holds the value for the amount of vowels in the current word */
  int threeVowelWords=0; /* Counts the amount of words with more than three vowels */
  int threeVowels = 3; /* Number of vowels each word is being checked for. */


  vowelCounter = vowel_count(word); /* Computes the current amount of vowels in the word by calling the vowel_count function. */

  /* Checks if the current word has more than three vowels and if it does it increments the threeVowelWords variable. */
  if(vowelCounter >= threeVowels){
    threeVowelWords++;
  }
  return (threeVowelWords); /* Returns the number of words with more than three vowels. */
}


/* Code for the is_palindrome function. */

int is_palindrome (char word[]){

  /* The input parameter word represents an array of chars. This functions checks if that word is a palindrome, which means that it can be spelled backwards. Single letter words are considered palindromes. */

  int i = strlen(word)-1; /* Counter that starts at the last char of the word. */
  int j=0; /* Counter that starts at the beginning char of the word. */

  /* Loop that compares each char of the word from beginning to end and from end to beginning and returns one if the results are the same. */
  while(j<i){
    if(word[j] != word[i]){
      return 0;
    }
    i--;
    j++;
  }
  return 1;
}
