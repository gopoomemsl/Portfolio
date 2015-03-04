/******************************************************************************
cs2123p1.c by Paul Szyller
Purpose:
    This file contains the convertToPostFix function for the goal of reading queries 
    and converting them from infix to postfix. 
Command Parameters:
    n/a
Input:
    The input comes from the cs2123p1Driver.c file and is described in said file.
Results:
    Takes a querry and converts it from infix to postfix.
Returns:
    The returns are handled in cs2123p1Driver.c where the main function is and are
    descrived there.
Notes:
    This program only contains the convertToPostFix function requiered for the
    project 1 assignment. Most of the code is actually contained in cs2123p1Driver.c
    and cs2123p1.h.
*******************************************************************************/

#include <string.h>
#include "cs2123p1.h"
/**********************************************************************
cs2123p1.h
Purpose: 
Header file for this program.
Notes:
This is one of the 3 files provided by Dr. Clark for the project 1 assignment,
the other two provided files being cs2123p1Driver.c and cs2123p1Input.txt.
**********************************************************************/


/******************** convertToPostFix **************************************
int convertToPostFix(char *pszInfix, Out out)
Purpose:
    Convert a querry line from the infix form to the postfix form.
Parameters:
    I   char *pszInfix       		Input querry to be converted.
    O   Out out					        Returned output querry in postfix form.
Returns:
    Functionally:
        Integer representing the success of the operation or error encountered.
        0 - success.
        WARN_MISSING_LPAREN - input is missing a left parenthesis.
        WARN_MISSING_RPAREN - input is missing a right parenthesis.
    out parm - the converted querry.
Notes:
**************************************************************************/
int convertToPostFix(char *pszInfix, Out out)
{

	Stack stack = newStack();	
	Token szToken; //token string to store in Element variables
	
	while ((pszInfix = getToken(pszInfix, szToken, MAX_TOKEN + 1)) != 0) //while there are tokens in the line of input
	{
		/***Element set up***/		
		Element element;
		strcpy(element.szToken, szToken); //store the token in the element
		categorize(&element); //initialize the Element variable's values based on the token string entered
    
    
		/***Actual conversion***/		
		switch (element.iCategory) //what kind of element is it?
		{
			case CAT_OPERAND:
				addOut(out, element);
				break;

			case CAT_OPERATOR:
				while(isEmpty(stack) == FALSE && element.iPrecedence < topElement(stack).iPrecedence)
				//loop until the stack is empty or there's no more operator in the stack with a lower precedence than the top of the stack 
				{
					addOut(out, pop(stack)); //POP and OUT the higher precedence operator from the stack
				}
				push(stack, element);
				break;

			case CAT_LPAREN:
				push(stack, element);
				break;

			case CAT_RPAREN:
				while (isEmpty(stack) == FALSE && topElement(stack).iCategory != CAT_LPAREN)
				{
					addOut(out, pop(stack)); //POP and OUT content of the stack until left parenthesis is found
				}
				
				if (isEmpty(stack) == TRUE) //if we didn't find a (
				{
					freeStack(stack); //at this point we are done using the stack
					return WARN_MISSING_LPAREN; //return error
				}
				pop(stack); //POP and get rid of (
				break;
		}
	}
	
	/***Remaining Stack***/
	while (isEmpty(stack) == FALSE)	//goes through the remaining stack until empty
	{
		if (topElement(stack).iCategory == CAT_LPAREN)//if an unmatched ( is found
		{
			freeStack(stack); //at this point we are done using the stack
			return WARN_MISSING_RPAREN; //return error
		}
		
		addOut(out, pop(stack)); //POP and OUT the stack
	}
	
	freeStack(stack); //at this point we are done using the stack		
	return 0; //return success
}
