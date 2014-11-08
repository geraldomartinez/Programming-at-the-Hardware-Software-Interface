/*
Geraldo Martinez
gm979351
Fri_1_40

Ryan Scanlan
rs993355
Fri_1_40

We both worked on the project together, we each decided on working on separate functions and then testing them together as we got them to function properly.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_ARG 2 /* Number of parameters that main function takes in. */
#define FILE_ARG 1 /* Position in argv that the file will be. */

#define START_LEN 80 /* Size that the array is initialized to. */
#define INCREMENT 40 /* Amount in which the char array will be incremented when needed. */

/* Prototypes of all the functions used in the program. */
char *NextLine (FILE *);
void stat (char *);
void prpat (char *, char *);
void first (int, char *);
void last (int, char *);
void trunc (int, char *);
void diff (char *, char *);
int line_length(char *);

/*
The main method was coded by the both of us since we each had to test it for individual purposes for the functions we wrote.

Main method that takes in two parameters one of type int and one of type char. Executes all of the functions and process the information inputted in the files. 
*/
int main(int argc, char *argv[]){

  FILE *inf; /* Variable of type FILE that is used to control the file inputted. */
  char *line; /* Variable that will store the line of the file. */
  char *command; /* Holds the command passed by the command file. */
  char *parameter_1; /* Holds the first parameter found in the command file. */
  char *parameter_2; /* Holds the second parameter found in the command file. */

  /* If the program doesn't receive two parameters, then it prints error message. */
  if(argc != NUMBER_ARG){
    fprintf(stderr, "Invalid number of command line arguments.\n");
    exit(1);
    }

  /* Prints error message if the file could not be opened for reading. */
  if((inf = fopen(argv[FILE_ARG], "r"))==NULL){
    fprintf(stderr, "Could not open the file: %s.\n",argv[FILE_ARG]);
    exit(1);
  }

  /* While the lines in the files contain a command it runs this loop. */
  while((line = NextLine(inf))!=NULL){
    command =strtok(line," "); /* Discover the command. */

    /* If the command is stat it calls that function. */
    if(strcmp(command, "stat")==0) 
      {
	parameter_1=strtok(NULL," ");
	stat(parameter_1);
      }

    /* If the command is prpat it calls that function. */
    else if(strcmp(command, "prpat")==0){ 
      parameter_1=strtok(NULL," "); /* Gets the first parameter. */
      parameter_2=strtok(NULL," "); /* Gets the second parameter. */
      prpat(parameter_1, parameter_2);
    }

    /* If the command is first it calls that function. */
    else if(strcmp(command,"first")==0){
      parameter_1=strtok(NULL," "); /* Gets the first parameter. */
      parameter_2=strtok(NULL," "); /* Gets the second parameter. */
      first(atoi(parameter_1),parameter_2);
    }

    /* If the command is last it calls that function. */
    else if(strcmp(command,"last")==0){
      parameter_1 = strtok(NULL," "); /* Gets the first parameter. */
      parameter_2 = strtok(NULL," "); /* Gets the second parameter. */
      last(atoi(parameter_1), parameter_2);
    }

    /* If the command is trunc it calls that function. */
    else if(strcmp(command,"trunc")==0){
      parameter_1=strtok(NULL," "); /* Gets the first parameter. */
      parameter_2 = strtok(NULL," "); /* Gets the second parameter. */
      trunc(atoi(parameter_1),parameter_2);
    }

    /* If the command is diff it calls that function. */
    else if(strcmp(command,"diff")==0){
      parameter_1 = strtok(NULL," "); /* Gets the first parameter. */
      parameter_2 = strtok(NULL," "); /* Gets the second parameter. */
      diff(parameter_1,parameter_2);
    }

    /* There is no available command. */
    else{
      printf("Invalid command.\n");
      fflush(stdout);
    }
  }

  /* If the file cannot be closed, prints error message. */
  if (fclose(inf)==EOF){
    fprintf(stderr, "Error trying to close the file %s.\n", argv[FILE_ARG]);
    exit(1);
  }
  return 0;
} /* End of the main Function. */

/* Function that receives a file and returns the next line of it. Takes in a parameter of type FILE.

Coded by Geraldo Martinez
 */
char *NextLine (FILE *inf){

  char *line; /* Variable that will store the line of the file. */
  int c; /* Variable that will store each of the line. */
  int index; /* Used to access each position of the array. */	
  int newsize; /* Stores the new size of array if more space is needed. */
  newsize = START_LEN;
  index = 0;

  /* Allocates the initial space for the array. */
  if((line=(char*)malloc(newsize*sizeof(char)))==NULL){
    fprintf(stderr,"Error trying to allocate space.\n");
    exit(1);
  }

  /* If there are no more lines in the file. */
  if((c=getc(inf))==EOF){
    return NULL;
  }

  line[index++]=c; /* Stores the first character. */

  /* While does not find the break line character. */
  while((c=getc(inf))!='\n'){

    /* If it reaches the EOF. */
    if(c==EOF)
      break;
    line[index++]=c; /* Stores the character in the array. */

    /* If we need more space. */
    if(index==(newsize-1)){
      newsize+=INCREMENT; /* Increases the size of the array. */
      if((line=(char*)realloc(line, newsize*sizeof(char)))==NULL){
	fprintf(stderr,"Error trying to allocate more space.\n");
	exit(1);
      }
    }
  }
  line[index]='\0'; /* Stores the end character for a string. */
  return line;
} /* End of the NextLine function. */

/*
The stat function prints out statistcal information about the inputted file. It prints things such as the total number of lines in the file, the length of a longest line as well as the shortest, and the length of the average length of a line in the file. Takes in a parameter of type char.

Coded by Geraldo Martinez
*/
void stat (char *filename){

  FILE *inf; /* Pointer to the filename */
  char *line; /* Stores the line of the file. */
  int no_lines; /* Stores how many lines exist in the file. */
  int max_length; /* Store the length of the longest line in the file. */
  int min_short; /* Stores the length of the shortest line in the file. */
  int char_count1; /* Stores the amount of characters in one line. */
  int char_count2; /* Stores the ammount of characters in the file. */
  int index; /* Used to identify the position in the array. */
  double average; /* Stores the average length of a line in the file. */

  /* Initializes the variables. */
  no_lines=0;
  max_length=-1;
  min_short=-1;
  char_count1=0;
  char_count2=0;
  index=0;

  /* If file can't be opened for reading, prints out error message. */
  if((inf=fopen(filename, "r"))==NULL){
    printf("\nCommand = stat: Can't open file %s for reading.\n",filename);
    fflush(stdout);
  }
  else{

    /* While there are lines in the file. */
    while((line=NextLine(inf))!=NULL){
      no_lines++; /* Increments the number of lines */

      /* While the end of the line is not found. */
      while(line[index++]!='\0'){ 
	char_count1++; /* Increments the number of characters in the line. */
	char_count2++; /* Incremets the number of characters in the file. */
      }
      char_count1++; /* Update the variable to count the character \n */
      char_count2++; /* Update the variable to count the character \n */

      /* if it is the first time in the loop, then both line variables are set to char_count1. */
      if(max_length == -1 && min_short == -1){
	max_length = char_count1;
	min_short = char_count1;
      }
      else{

	/* Sets max length to char_count1 if it is lesser than char_count1. */
	if(char_count1 > max_length){
	  max_length = char_count1;
	}
	/* Sets min_short to char_count1 if it is greater than char_count1. */
	if(char_count1 < min_short){
	  min_short = char_count1;
	}
      }
      /* Resets the variables for the next loop run. */
      char_count1=0; 
      index=0;
    }
    /* If the file doesn't have any line then max_length should be -1 */
    if(max_length == -1){
      average=0.0;
      max_length =0;
      min_short =0;
    }
    else{
      /* Computes the average length of a line. */
      average = (double)char_count2/(double)no_lines;
    }
    /* Prints out the statistics of the file. */
    printf("\nNo. of lines        = %d \n", no_lines);
    fflush(stdout);
    printf("Maximum line length = %d \n",max_length);
    fflush(stdout);
    printf("Minimum line length = %d \n", min_short);
    fflush(stdout);
    printf("Average line length = %f \n", average);
    fflush(stdout);
  }
  /* If the file cannot be closed, prints out an error message. */
  if(fclose(inf)==EOF){
    printf("Error trying to close the file %s.\n", filename);
    fflush(stdout);
  }
} /* End of the stat function. */

/*
The prpat function takes in two char parameters, with the first one being a pattern in which you are looking for. If the pattern is found then it should print out each line of the file in which the pattern  is found in the file.

Coded by Ryan Scanlan
*/
void prpat (char *pattern, char *filename){

  FILE *inf; /* Pointer to the filename. */
  char *line; /* Stores the line of the file. */
  int verifier; /* Used to know if the pattern was found. 0 means no. 1 means yes. */
  verifier=0;

  /* Prints an error message if the file cannot be read. */
  if((inf=fopen(filename, "r"))==NULL){
    printf("\nCommand=prpat: Can't open file %s for reading.\n", filename);
    fflush(stdout);
  }
  else{

    /* While there are lines in the file. */
    while((line=NextLine(inf))!=NULL){

      /* If the string occurs in the string line print out that line. */
      if(strstr(line,pattern)!=NULL){
	verifier=1; /* Updates the verifier. */
	printf("%s\n", line);
	fflush(stdout);
      }
    }
    /* If the pattern isn't found it prints a message saying so. */
    if(verifier==0){
      printf("The specified pattern does not occur in the file.\n");
      fflush(stdout);
    }
  }
  /* If the file cannot be closed then it prints out a message saying so. */
  if(fclose(inf)==EOF){
    printf("Error trying to close the file %s.\n", filename);
    fflush(stdout);
  }
} /* End of the prpat function. */

/*
The first function takes in two parameters one being a number of lines wished to be checked for and the other is the char file. The function prints out the lines specified by the parameter.

Coded by Ryan Scanlan
 */
void first(int num, char *filename){

  FILE *inf; /* Points to the file. */
  char *line; /* Stores the line of the file. */
  int count = 0; /* Counter. */

  /* If file cannot be opened for reading, then it prints out error message. */
  if((inf=fopen(filename, "r"))==NULL){
    printf("\nCommand=first: Can't open file %s for reading.\n", filename);
    fflush(stdout);
  }
  else{
    /* Checks if the input num is greater than 0, if not prints error message. */
    if(num<=0){
      printf("\nThe integer in the parameter was not greater than 0\n");
      fflush(stdout);
    }
    else{
      printf("\n");
      fflush(stdout);
      
      /*Loops until line is null or the count variable is equal to num, prints the lines as it loops. */
      while((line=NextLine(inf))!=NULL && count < num){
	printf("%s\n", line);
	count++;
      }
    }

    /* If file cannot be closed then it prints out error message saying so. */
    if(fclose(inf)==EOF){
      printf("\nError trying to close the file %s.\n", filename);
      fflush(stdout);
    }
  }
} /* End of first function. */

/*
The function last is similar to taht of the first function. This function only prints the last num of lines of the specified file in the correct order.

Coded by Ryan Scanlan
*/
void last (int num, char *filename){

  FILE *inf; /* Pointer to the filename. */
  char *line; /* Stores the line of the file. */
  int i,k,counter; /* Used for holding places and counting. */
  char **answer; /* Pointer array of type char. */
  answer=(char **)malloc(num*sizeof(char**)); /* Creates space for the array in memory. */
  counter=0; /* Initializes counter to 0. */

  /* If the file cannot be opened for reading, prints out an error message. */
  if((inf=fopen(filename, "r"))==NULL){
    printf("\nCommand = last: Can't open file %s for reading.\n", filename);
    fflush(stdout);
  }
  else{
    /* If the number is less than 1, then it prints out message. */
    if(num<=0){
      printf("\nThe integer in the parameter was not greater than 0.\n");
      fflush(stdout);
    }
    else{
      /* Goes through array and sets every position to the '\0' */
      for(i=0;i<num;i++)
	answer[i]= "\0";
      i=0; /* Sets i equal to 0. */
      printf("\n");
      fflush(stdout);

      /* While loop that makes sure the line doesn't equal to NULL. */
      while((line=NextLine(inf))!=NULL){
	answer[i++]=line; /* Assigns answers at spot i to the value stored in line and then increments. */
	counter++; 

	/*Checks if i is equal to num.*/
	if(i==num){
	  i=0;
	}
      }

      /* Condition that checks to see if counter is less than num. */
      if(counter < num){

	/* Runs while k is less than the counter. */
	for(k=0;k<counter;k++){
	  printf("%s\n", answer[k]);
	}
      }
      else{
	/* Runs while k is less than num */
	for(k=0;k<num;k++){
	  if (i==num){
	    i=0; /* Sets i back to 0. */
	  }
	  printf("%s\n", answer[i++]); /* prints the value stored at the position of i. */
	}
      }
    }

    /* if file cannot be closed, prints out error message. */
    if(fclose(inf)==EOF){
      printf("Error trying to close the file %s.\n", filename);
      fflush(stdout);
    }
  }
} /* End of the last function. */

/* 
The trunc function takes in two parameters. One of type int and the other of type char. The function truncates lines in the file by the integer specified in the parameter. 

Coded by Geraldo Martinez.
 */
void trunc (int len, char *infile){
  FILE *inf; /* Points to the file */
  char *line; /* Stores the line in the file. */

  /* Checks if the file can be opened for reading, if not it prints saying so. */
  if((inf=fopen(infile, "r"))==NULL){
    printf("\nCommand = trunc: Can't open file %s for reading.\n", infile);
    fflush(stdout);
  }
  else{
    /* Checks if the length is atleast 3, if not it prints out saying so. */
    if(len<2){
      printf("\nCommand = trunc: Required Line Length = 1 is too small\n");
      fflush(stdout);
    }
    else{
      printf("\n");
      fflush(stdout);

      /* While there is a next line in the file. */
      while((line = NextLine(inf))!=NULL){

	/* Makes a call to the line_length function, and if the return is less than len it prints out that line. */
	if(line_length(line)<len){
	  printf("%s\n", line);
	}
	else{
	  line[len-1]='\0'; /* Sets the character at the end of the line to '\0'. */
	  printf("%s\n", line); /* Prints out the line. */
	}
      }
    }
    /* Attempts to close the file, prints out an error message if it fails to.*/
    if(fclose(inf)==EOF){
      printf("Error trying to close the file %s.\n", infile);
      fflush(stdout);
    }
  }
} /* End of the trunc function. */

/*
  The function diff takes in two parameter of type char that represent two files. The function compares both files and checks if the files are identical, if they are not, it prints out saying so and where the file isn't identical. 

Coded by Geraldo Martinez.
*/
void diff (char *file1, char *file2){

  FILE *inf1; /* Points to the first file. */
  FILE *inf2; /* Points to the second file. */
  char *line1; /* Stores the lines of file1. */
  char *line2; /* Stores the lines of file2. */
  int answer; /* Checks if the files are identical. If answer =0 then they are not identical. */
  int i; /* Counter */
  answer = 1; /* Assigns a value to answer. */

  /* Checks to see if either file is equal to Null and is opened for reading. */
  if((inf1=fopen(file1, "r"))==NULL || (inf2 = fopen(file2, "r"))==NULL){

    /* If file is null then it prints out error message. */
    if(inf1==NULL){
      printf("\nCommand = diff: Can't open file %s for reading.\n", file1);
      fflush(stdout);
      }
    else{

      /* If file is null then prints out error message. */
      if(inf2==NULL){
	printf("\nCommand = diff: Can't open file %s for reading.\n", file2);
	fflush(stdout);
      }
    }
  }
  else{
    line1= NextLine(inf1); /* Stores the first line of file1 onto line1. */
    line2=NextLine(inf2); /* Stores the first line of file2 onto line2. */

    /* Runs until line1 & line2 are equal to null. */
    for(i=1;1;i++){

      /* if the two lines are the same. */
      if(strcmp(line1,line2)!=0){
	answer=0;
	break;
      }

      /*Sets line1 and line2 to the next line of their corresponding files. */
      line1=NextLine(inf1);
      line2=NextLine(inf2);

      /* if line1 and line2 is Null, then it breaks out of the loop.*/
      if(line1==NULL && line2==NULL)
	break;

      /* Conditional that checks to see if line1 is equal to null and line 2 isn't and vice versa. */
      if((line1==NULL && line2 != NULL) || (line1 != NULL && line2 == NULL)){
	answer=2;
	printf("\nThe files are different. The first difference is in line %d\n", i+1);
	fflush(stdout);
	break;
      }
    }
    /* conditional statement that checks to see if answer is equal to 0. */
    if(answer==0){
      printf("\nThe files are different. The first difference is in line %d\n", i);
      fflush(stdout);
    }
    else{
      /* If answer is equal to 1, then the files are the same. */
      if(answer==1){
	printf("\nThe files are identical.\n");
	fflush(stdout);
      }
    }
  }

  /* attempts to close file1, if there is an error it prints out saying so. */
  if(fclose(inf1)==EOF){
    printf("Error trying to close the file %s.\n", file1);
    fflush(stdout);
  }
  else{
    /* Attempts to close file2, if theres an error it prints out saying so. */
    if(fclose(inf2)==EOF){
      printf("Error trying to close the file %s.\n", file2);
      fflush(stdout);
    }
  }
} /* End of diff function. */

/*
  the function line_length returns the number of chars in a line passed by the parameter.
Coded by Geraldo Martinez.
*/
int line_length(char *line){
  int i=0;
  while(line[i]!='\0'){
    i++;
  }
  return i;
}
