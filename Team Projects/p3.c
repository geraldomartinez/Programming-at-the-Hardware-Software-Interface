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

/* Array size for the command input. */
#define array_size 4

/*Creates a linked list that holds two integer values (coefficient & exponent). */
typedef struct node {
  int value; /* Represents the coefficient in a node in the list. */
  int value2; /* Represents the exponent in a node in the list. */
  struct node *next;
} NODE, *PNODE;

/* Prototypes of all the functions used in the program. */
void prp(PNODE );
void pvp(PNODE , int);
void prd(PNODE );
void prc(PNODE , int);
void plc(PNODE );
void psc(PNODE );
void adc(PNODE *, int, int);
void dex(PNODE *, int);
void insert_node (PNODE *, int, int, int);
void der(PNODE *, int, int);

/*
The main method was coded by the both of us since we each had to test it for individual purposes for the functions we wrote. 

Main method that executes all of the functions and takes in all of the inputs from the users.
 */
int main(void){

  /* char variable that holds the input entered by the user. */
  char command[array_size]; 
  /* Variable that stores the coefficient being passed by the adc command. */
  int coefficient;
  /* Variable that stores the exponent being passed by the adc command. */
  int exponent;
  /* Variable that stores the exponent being passed by the dex command. */
  int exp;
  /* Variable that stores the first exponent being passed by the der command. */
  int derEXP1;
  /* Variable that stores the second exponent being passed by the der command. */
  int derEXP2;
  /* Variable that stores the exponent being passed by the prc command. */
  int y;
  /* Variable that stores the x value being passed by the pvp command. */
  int x;

  /* Creates a node called head. */
  PNODE head;
  /* Initialized the node to NULL. */
  head = NULL;

  /*Print statements for the user to know what commands to choose from. */

  printf("Please choose from one of the following commands: \n");
  fflush(stdout);
  printf("adc, dex, der, prp, pvp, prd, prc, plc, psc or end.\n");
  fflush(stdout);

  /* Prompts the user for a command to be passed to the program. */
  scanf("%s", command);

  /* Loop that promps user for a command until command is not "end". */
  while(strcmp (command, "end")!=0){

    if(strcmp (command, "adc")==0){
      scanf("%d%d", &coefficient, &exponent);
      adc(&head, coefficient, exponent);
    }

    if(strcmp (command, "dex")==0){
      scanf("%d", &exp);
      dex(&head, exp);
    }

    if(strcmp (command, "der")==0){
      scanf("%d%d", &derEXP1, &derEXP2);
      der(&head, derEXP1, derEXP2);
    }

    if(strcmp (command, "prp")==0){
      prp(head);
    }

    if(strcmp (command, "pvp")==0){
      scanf("%d", &x);
      pvp(head, x);
    }

    if(strcmp (command, "prd")==0){
      prd(head);
    }

    if(strcmp (command, "prc")==0){
      scanf("%d", &y);
      prc(head, y);
    }

    if(strcmp (command, "plc")==0){
      plc(head);
    }

    if(strcmp (command, "psc")==0){
      psc(head);
    }

    printf("Another command?: \n");
    fflush(stdout);

    /* Asks for another command inside the loop to keep the program running. */
    scanf("%s", command);
  } /* End of while loop */

  printf("Program ended successfully.\n");
  fflush(stdout);

  return 0;
}

/* The function prp prints the list passed by the parameter PNODE h, if the coefficient value is positive, it prints out a "+" sign. */
void prp(PNODE h){
  /* Condition that prints a "0 x^0" to represent an empty list when a list is empty.
Worked on by Geraldo Martinez
 */
  if (h == NULL){
    printf("0 x^0\n");
    fflush(stdout);
  }

  else {
    printf("Values in the list are:\n");
    fflush(stdout);

    /* While loop that runs through all the node until the list is equal to NULL */
    while(h!=NULL){
      /* If the coefficient is more or equal to zero, then print a "+" before the coefficient. */
      if(h->value >= 0){
	printf("+");
	fflush(stdout);
      }
      /* Prints the rest of the coefficient as the loop runs */
      printf("%d", h->value);
      fflush(stdout);
      printf(" x^");
      fflush(stdout);
      printf("%d", h->value2);
      fflush(stdout);
      printf(" ");
      fflush(stdout);
      h=h->next;
    }
    printf("\n");
    fflush(stdout);
  }
}
/* End of prp function */

/* This function inserts a node into the list, takes in a node, and three int values.
Worked on by Geraldo Martinez
 */
void insert_node(PNODE *h, int coef, int exp, int position){

  /* Creates a node called temp. */
  PNODE temp;

  /* If statement that checks to see if node is equal to NULL when you tried to create space. */
  if ((temp = (PNODE)malloc(sizeof(NODE)))==NULL){
    printf("Node allocation failed. \n");
    fflush(stdout);
    /* exits out of the function */
    exit(1);
  }

  /* Sets the temp node to the value of the coefficient and the exponent. */
  temp->value=coef;
  temp->value2=exp;

  /* If the list is empty it inserts the node in the first position */
  if(position ==0){
    temp->next = NULL;
    *h = temp;
  }

  /* inserts the node into the first position if the position variable is equal to 1 */
  else if (position == 1){
    temp->next = *h;
    *h = temp;
  }

  /* Inserts the node into the middle if position is equal to 2. */
  else if (position == 2){
    temp->next = (*h)->next;
    (*h)->next = temp;
  }
}
/* End of insert_node function */

/* Function that adds a node into the list, and takes in a node and one coefficient and exponent corresponding to the list.

Worked on by Geraldo Martinez
 */
void adc(PNODE *head, int coef, int exp){
  PNODE temp = *head; /* Local variable PNODE */
  int verifier = 0; /* Local int variable that is used to check cases of when lsit is empty */

  /* Case to check if list is empty, and if it is it inserts a node. */
  if (*head == NULL){
    insert_node(head, coef, exp, 0);
  }
  else{
    /* if statements that inserts a new node in the first position. */
    if ((*head)->value2 < exp){
      insert_node(head, coef, exp, 1);
    }
    /* If the exponents are the same, it adds the coefficients together. */
    else if((*head)->value2 == exp){
      if(((*head)->value + coef) != 0){
	(*head)->value = (*head)->value + coef;
      }
      /* Deletes the node if the sum is zero. */
      else{ 
	dex(head, exp);
      }
    }
    else{
      /* Loop that runs through all of the nodes in the list. */
      while(temp->next != NULL){
	/* if statement that checks to see if the temp node next exponent is equal to the exp. */
	if((temp->next)->value2 == exp){
	  if (((temp->next)->value + coef) != 0){
	    (temp->next)->value = (temp->next)->value + coef;
	  }
	  else{
	    /* if the if statement is false then it deletes the node. */
	    dex(head, exp);
	  }
	  /* sets verifier to 1 */
	  verifier = 1;
	  break;
	}
	/* If statement that checks to see if the temp nodes next exponent minus exp is less than 0 */
	else if (((temp->next)->value2 - exp) < 0){
	  insert_node(&temp, coef, exp, 2);
	  verifier = 1;
	  break;
	}
	temp = temp->next;
      }
      /* end of while loop */

      /* if statement that checks to see if the temp nodes next is equal to NULL. */
      if(temp->next == NULL && verifier == 0){
	insert_node(&temp, coef, exp, 2);
	}
    }
  }
}/* End of the adc function. */

/* Function that deletes the node of the polynomial where the exponent is equal to the value given by exp. Takes a node and an int value. 
Worked on by Ryan Scanlan.
*/

void dex(PNODE *h, int exp){
  /* declares two Node variables used in the function. */
  PNODE temp= *h;
  PNODE del;
 
  /* if the list is empty it prints out a statement saying so. */
  if(temp == NULL)
    {
      printf("No exponent to delete available. \n");
      fflush(stdout);
    }  
  else{
    /* if the exp equals to the current node in the list, then it deletes such node. */
    if ((*h)->value2 == exp){
      (*h)=(*h)->next;
      free(temp);
    }
    else{
      /* Loops through the list and reorganizes nodes and points it to each other. */
      while(temp->next != NULL){
	if((temp->next)->value2==exp){
	  break;
	}
	temp = temp->next;
      }
      if(temp->next != NULL){
	del= temp->next;
	temp->next=(temp->next)->next;
	free(del);
      }
    }
  }
}/* end of the dex function. */

/*
  Function that deletes each node of the polynomial where the exponent value is in the range given by exponent 1 and exponent 2. Takes in a node and 2 int values.
 
Worked on by Ryan Scanlan

*/
void der(PNODE *head, int exponent1, int exponent2){
  int i; /* local variable used for counter in the loop. */
  /* Loops from the first exponent until the second exponent. */
  for (i=exponent1; i<= exponent2; i++){
    dex(head, i); /* calls the delete function on the list. */
  }
}/* end of the der function */

/* Function that finds the value of the polynomial obtained by setting the variable x to the value given by val and prints the resulting value. Takes in a node and an int value.
Worked on by Geraldo Martinez
*/
void pvp(PNODE h, int val){
  int x=0; /* local variable that holds the result of the computation. */
  int value=val; 
  int i; /* loop counter */

  /* If the list is empty then it prints out a zero. */
  if(h==NULL){
    printf("0\n");
    fflush(stdout);
  }
  else{
    /* Runs until list is empty, computes the x value passed by the parameter. */
    while(h!=NULL){
      value=val;
      /* if the exponent is 0, then sets the value to 1. */
      if (h->value2 == 0){
	value = 1;
      }
      else{
	value = val;
	/* Loops to multiply the amount of times that the power is raised to */
	for(i=1; i<h->value2; i++){
	  value=value*val;
	}
      }

      x+= value * (h->value); /* Multiplies the value raised by the current coefficient and then adds it to x. */
      h=h->next;
    }
    /* Prints the value x. */
    printf("%d\n", x);
    fflush(stdout);
  }
} /* end of the pvp function. */

/* Function that prints the degree of the polynomial. Takes in a node. 
Worked on by Ryan Scanlan
*/

void prd(PNODE h){
  /* If the list is empty then it prints zero. */
  if(h==NULL){
    printf("0\n");
    fflush(stdout);
  }
  else
    /* if the list is empty, prints out the first coefficient in the list since it is the one with the highest exponent. */
    {
      printf("%d\n", h->value2);
      fflush(stdout);
    }
}/* End of the prd function */

/* 
   Function that prints the coefficient of the term whose exponent is given by e. Takes in a node and an int value.

Worked on by Geraldo Martinez
*/
void prc(PNODE h, int e){
  int x=0; /* local variable in function. */

  /* if the list is empty, then it prints out zero. */
  if(h==NULL){
    printf("0\n");
    fflush(stdout);
  }
  else{
    /* Loops until list is empty and sets x to the coefficient reffering to the exponent of that coefficient. */
    while(h!=NULL){
      if(h->value2 == e){
	x=h->value;
      }
      h=h->next;
    }
    printf("The coefficient of the exponent is %d\n", x);
    fflush(stdout);
  }
} /* End of the prc Function. */

/*
  Function that prints the largest coefficient value among all the terms in the polynomial. Takes in a node.
*/
void plc(PNODE h){

  int x; /* Local variable that holds the value of the next coefficient in the list. */

  /* If statement that prints out zero if the list is empty. */
  if(h==NULL){
    printf("0\n");
    fflush(stdout);
  }

  else{
    x=h->next->value; /* sets variable x to the next coefficient in the list. */
    /* while loop that runs through the list until it equals null and sets x to the highest coefficient. */
    while(h!=NULL){
      if(x <= h->value){
	x=h->value;
      }
      h=h->next;
    }
    printf("%d\n", x);
    fflush(stdout);
  }
} /* end of the plc function. */

/* The psc functions prints the lowest coefficient in the list passed by the parameter PNODE h.
Worked on by Geraldo Martinez
 */
void psc(PNODE h){

  int x; /* Local variable that holds the coefficient of the next node in the list. */

  /* If statement that checks if the list is empty, if it is it prints out "0". */
  if(h==NULL){
    printf("0\n");
    fflush(stdout);
  }

  else{
    x=h->next->value; /* sets the x to the coefficient pointed by the next in the list. */
    /* While loop that runs until list is NULL and sets x to smallest coefficient in the list. */
    while(h!=NULL){
      if(x >= h->value){
	x=h->value;
      }
      h=h->next;/* Points the node to the next node to keep the loop running. */
    }
    printf("%d\n", x);
    fflush(stdout);
  }
}
