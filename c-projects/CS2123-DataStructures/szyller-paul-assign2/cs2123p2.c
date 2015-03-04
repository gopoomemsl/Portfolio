/******************************************************************************
cs2123p2.c by Paul Szyller
Purpose:
    This file is part of a larger program which goals it is to read queries, convert
    them from infix to postfix, and execute the queries.
    This file contains the printCustomerData function, convertToPostFix function, 
    evaluatePostfix function, and the smaller functions necessary for those. 
Command Parameters:
    n/a
Input:
    The input comes from the cs2123p2Driver.c file and is described in said file.
Results:
    -Prints the customer infos from a Customer array.
    -Converts a infix querry to postfix notation.
    -Evaluate a postfix querry and returns the results in a boolean array.
Returns:
    The returns of the program are handled in cs2123p1Driver.c where the main function 
    is and are described there.
Notes:
    This program only contains the functions requiered for the
    project 2 assignment. Most of the code is actually contained in cs2123p2Driver.c
    and cs2123p2.h, both created by Larry Clark.
*******************************************************************************/



/*** Includes ***/

#include <string.h>
#include <stdio.h>
#include "cs2123p2.h"
/******************************************************************************
cs2123p2.h
Purpose: 
    Header file for this program.
Notes:
    This is one of the four files provided by Dr. Clark for the project 2 assignment,
    the other three provided files being cs2123p2Driver.c, and the two input files 
    p2customer.txt and p2query.txt
*******************************************************************************/



/*** Warning constants ***/
#define WARN_NOT_ENOUGH_OPER 803
#define WARN_TOO_MANY_OPER 804



/*** Prototypes for additional functions ***/
//Program 1
void convertSubTaskOperand(Out out, Element *pElement);
void convertSubTaskOperator(Stack stack, Out out, Element *pElement);
void convertSubTaskLParen(Stack stack, Element *pElement);
int convertSubTaskRParen(Stack stack, Out out);
int convertSubTaskRemainingStack(Stack stack, Out out);

//Program 2
int popTwoOperands(Stack stack, Element *pOperand1, Element *pOperand2);
Element operatorHandling(Element *pOperand1, Element *pOperand2, Element *pOperator, Customer *pCustomer);
int and(Element *pOperand1, Element *pOperand2);
int or(Element *pOperand1, Element *pOperand2);
void warningExit(int iWarningCode, QueryResult resultM[], Stack stack);



/*** Functions ***/

/********************printCustomerData*****************************************
void printCustomerData(Customer customerM[], int iNumCustomer)
Purpose:
    Prints a formated version of the customerM[] array.
Parameters:
    I Customer customerM[]  customer array to print out.
    I int *piNumCustomer    number of Customers in the array customerM.
Notes:
Return Value:
    void
*******************************************************************************/
void printCustomerData(Customer customerM[], int iNumCustomer)
{
    int i;
    int j;
    
    //print a heading for the list of customers and traits
    printf("%-6s\t%-20s\n\t\t%-10s\t%-12s\n", "ID", "Customer Name", "Trait", "Value");

    //for each customer
    for (i = 0; i < iNumCustomer; i++)
    {
        //print the customer information
        printf("%-6s\t%-20s\n", customerM[i].szCustomerId, customerM[i].szCustomerName);

        //goes through the array of Trait for each customer
        for (j = 0; j < customerM[i].iNumberOfTraits; j++)
        {
            //print a trait
            printf("\t\t%-10s\t%-12s\n", customerM[i].traitM[j].szTraitType, customerM[i].traitM[j].szTraitValue);
        }
    }
    printf("\n");
}

/*********************** convertToPostFix **************************************
int convertToPostFix(char *pszInfix, Out out)
Purpose:
    Convert a querry line from the infix form to the postfix form.
Parameters:
    I   char *pszInfix      Input querry to be converted.
    O   Out out             Returned output querry in postfix form.
Returns:
    Functionally:
        Integer representing the success of the operation or error encountered.
        0 - success.
        WARN_MISSING_LPAREN - input is missing a left parenthesis.
        WARN_MISSING_RPAREN - input is missing a right parenthesis.
    out parm - the converted querry.
Notes: 
    Modified from prgrm1 version to add modularity and fix output.
*******************************************************************************/
int convertToPostFix(char *pszInfix, Out out)
{
    /***Variables***/
    Stack stack = newStack();	
    Token szToken; //token string to store in Element variables
    Element element;
    
    /***conversion***/
    while ((pszInfix = getToken(pszInfix, szToken, MAX_TOKEN + 1)) != 0) //while there are tokens in the line of input
    {
        /***Element set up***/		
        strcpy(element.szToken, szToken); //store the token in the element
        categorize(&element); //initialize the Element variable's values based on the token string entered

        /***Actual conversion***/		
        switch (element.iCategory) //what kind of element is it?
        {
            case CAT_OPERAND:
                convertSubTaskOperand(out, &element);
                break;

            case CAT_OPERATOR:
                convertSubTaskOperator(stack, out, &element);
                break;

            case CAT_LPAREN:
                convertSubTaskLParen(stack, &element);
                break;

            case CAT_RPAREN:
                if (convertSubTaskRParen(stack, out) == WARN_MISSING_LPAREN)
                {
                    return WARN_MISSING_LPAREN;
                }
                break;
        }
    }
	
    /***Remaining Stack***/
    if (convertSubTaskRemainingStack(stack, out) == WARN_MISSING_RPAREN)
    {
        return WARN_MISSING_RPAREN;
    }
    return 0; //return success
}

/*******************************************************************************
void convertSubTaskOperand(Out out, Element *pElement)
Purpose:
    This function handles the case of an operand token.
    The operand element simply gets added to the out.
Parameters:
    O Out out		    The out structure used in the conversion.
    I Element *pElement	    The operand element.
Returns:
    out parm - the updated out structure.
Notes:
    This is a sub task of the query conversion from infix format to 
    postfix format.
*******************************************************************************/
void convertSubTaskOperand(Out out, Element *pElement)
{
    addOut(out, *pElement);
}

/*******************************************************************************
void convertSubTaskOperator(Stack stack, Out out, Element *pElement)
Purpose:
    This function handles the case of an operator token.
    The operators in the stack with a higher or equal precedence get outted 
    and the new operator gets pushed to the stack.		
Parameters:
    I/O Stack stack	    The current stack.
    O Out out		    The out structure used in the conversion.
    I Element *pElement	    The operator element.
Returns:
    stack parm - the updated stack.
    out parm - the updated out structure.
Notes:
    This is a sub task of the query conversion from infix format to 
    postfix format.
*******************************************************************************/
void convertSubTaskOperator(Stack stack, Out out, Element *pElement)
{
    while(isEmpty(stack) == FALSE && pElement->iPrecedence <= topElement(stack).iPrecedence)
    //loop until the stack is empty or there's no more operator in the stack with a lower
    //precedence than the top of the stack 
    {
        addOut(out, pop(stack)); //POP and OUT the higher precedence operator from the stack
    }
    push(stack, *pElement);
}

/*******************************************************************************
void convertSubTaskLParen(Stack stack, Element *pElement)
Purpose:
    This function handles the case of a left parenthesis token.
    The parenthesis element simply gets pushed to the stack.
Parameters:
    O Stack stack	    The current stack.
    I Element *pElement	    The left parenthesis.
Returns:
    stack parm - the updated stack.
Notes:
    This is a sub task of the query conversion from infix format to 
    postfix format.
*******************************************************************************/
void convertSubTaskLParen(Stack stack, Element *pElement)
{
    push(stack, *pElement);
}

/*******************************************************************************
int convertSubTaskRParen(Stack stack, Out out)
Purpose:
    This function handles the case of a right parenthesis token.
    The elements in the stack get outted until we find the matching 
    right parenthesis if there is one.
Parameters:
    I/O Stack stack	The current stack.
    O Out out		The out structure used in the conversion.
Returns:
    stack parm - the updated stack.
    out parm - the updated out structure.
Notes:
    This is a sub task of the query conversion from infix format to 
    postfix format.
*******************************************************************************/
int convertSubTaskRParen(Stack stack, Out out)
{
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
}

/*******************************************************************************
int convertSubTaskRemainingStack(Stack stack, Out out)
Purpose:
    This function handles the rest of the stack once we've gone through 
    all of the tokens in the input. It also handles the case of a leftover
    unmatched parenthesis in the stack.
Parameters:
    I/O Stack stack	The current stack.
    O Out out	        The out structure used in the conversion.
Returns:
    stack parm - the freed stack.
    out parm - the final out structure.
Notes:
    This is a sub task of the query conversion from infix format to 
    postfix format.
*******************************************************************************/
int convertSubTaskRemainingStack(Stack stack, Out out)
{
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
}

/***************************** evaluatePostfix ********************************
void evaluatePostfix(Out out, Customer customerM[], int iNumCustomer, QueryResult resultM[])
Purpose:
    This function takes in a query in postfix form and evaluate it to return 
    an array of booleans representing each customer that the query returns.
Parameters:
    I Out out			The query in postfix format.
    I Customer customerM[]	The array of customer for which the query will 
				be evaluated.
    I int iNumCustomer		The number of customers in customerM[].
    O QuerryResult resultM[]	The array of QuerryResult (booleans) representing 
                                which customer satisfy the conditions of the query.
Notes:
    The function will call a warning function to return an empty resultM[] and print 
    a warning message if an query is invalid.
Return value:
    resultM[] parm - An array of QueryResult, each boolean represent the customer 
                    of the same index in customerM[].
*******************************************************************************/
void evaluatePostfix(Out out, Customer customerM[], int iNumCustomer, QueryResult resultM[])
{
    Stack stack = newStack();
    Customer currentCustomer;
    Element operand1, operand2, evalElem, postElem;
    int i, j, iPopResult;
    
    for (i = 0; i < iNumCustomer; i++) //for each customer
    {
        currentCustomer = customerM[i]; //the current customer
    		
        for (j = 0; j < out->iOutCount; j++) //for each token in the postfix query
        {
            postElem = out->outM[j]; //the current token
	
            switch (postElem.iCategory)
            {				
                case CAT_OPERAND: 
                    //if token is an operand, just push
                    push(stack, postElem);
                    break;
					
                case CAT_OPERATOR:
                    iPopResult = popTwoOperands(stack, &operand1, &operand2);
                    //pop 2 operands and store them in operand1 and operand2                                        
        	    switch (iPopResult)
        	    {
        	        case 0:
        		    //call operator handling function
        		    evalElem = operatorHandling(&operand1, &operand2, &postElem, &currentCustomer);
        		    push(stack, evalElem); //push current result to stack
            		    break;
        
        		case WARN_NOT_ENOUGH_OPER:
        		    warningExit(WARN_NOT_ENOUGH_OPER, resultM, stack);
            		    return; //stop evaluating this query
        	    }        						
                    break;					
            }
        }
        
        //there should only be one element in the stack when the evaluation is over
        //we pop that element and send in to the result array at the index of the current customer
        resultM[i] = (pop(stack)).bInclude;        
        if(isEmpty(stack) == FALSE)
        {
            warningExit(WARN_TOO_MANY_OPER, resultM, stack);
            return; //stop evaluating this query
        }
    }
	
    freeStack(stack);
}

/************************* popTwoOperands **************************************
int popTwoOperands(Stack stack, Element *pOperand1, Element *pOperand2)
Purpose:
    This function will pop two elements from the given stack and store
    them in two Element variables.
Parameters:
    I/O Stack stack	    The stack to pop the two operands from.
    O Element *pOperand1    The Element variable to store the first operand in.
    O Element *pOperand2    The Element variable to store the second operand in.
Notes:
    Since the elements are poped starting from the end of the stack,
    the first element poped is stored as the second operand.
Return value:
    Functionally:
        Integer representing the success of the operation or error encountered.
        0 - success.
        WARN_NOT_ENOUGH_OPER - not enough elements to pop in stack or the elements
        		    poped are of incorrect types.
    stack parm - The stack with two elements poped.
    *pOperand2 parm - First element poped.
    *pOperand1 parm -	Second element poped.
*******************************************************************************/
int popTwoOperands(Stack stack, Element *pElem1, Element *pElem2)
{
    if (stack->iCount < 2)
    {
        return WARN_NOT_ENOUGH_OPER;
    }
		
    *pElem2 = pop(stack); 
    *pElem1 = pop(stack);
    		
    int bElem1Bool = (strncmp(pElem1->szBoolean, "Boolean", 7) == 0); 
    //will be TRUE if pOperand1 has a szBoolean that has been initialized to "Boolean result..."
    int bElem2Bool = (strncmp(pElem2->szBoolean, "Boolean", 7) == 0); 
    //will be TRUE if pOperand2 has a szBoolean that has been initialized to "Boolean result..."
    int bTypeMatch = (bElem1Bool == bElem2Bool);
    //will be TRUE if both elem are boolean structs or both token structs
    int bOperator = ((pElem1->iCategory == CAT_OPERATOR) || (pElem2->iCategory == CAT_OPERATOR));
    //will be TRUE if either elem is an operator
    
    if (bTypeMatch == TRUE && bOperator == FALSE)
    {
        return 0;
        //Only return success if both elements are operand tokens or both boolean structs
    }
    return WARN_NOT_ENOUGH_OPER; //else return error
}

/************************** operatorHandling ***********************************
Element operatorHandling(Element *pOperand1, Element *pOperand2, Element *pOperator, Customer *pCustomer)
Purpose:
    This function handles an operation of type AND, OR, =, NOTANY, or ONLY on 
    two operands.
Parameters:
    I Element *pOperand1    The first of the two operands.
    I Element *pOperand2    The second operand.
    I Element *pOperator    The operator element for this operation.
    I Customer *pCustomer   The customer for which the operations need to be true.
Notes:
Return value:
    A boolean Element containing the result of the operation.
*******************************************************************************/
Element operatorHandling(Element *pOperand1, Element *pOperand2, Element *pOperator, Customer *pCustomer)
{
    Element result;
    Trait currentTrait;
	
    char *szOperatorM[] = {"=", "NOTANY", "ONLY", "AND", "OR"};
    int i;	
    for (i = 0; (strcmp(pOperator->szToken, szOperatorM[i]) != 0); i++);
    //will stop when i = the index of our operator in szOperatorM[]
	
    switch (i)
    {
        case 0: //=
	    strcpy(currentTrait.szTraitType, pOperand1->szToken);
	    strcpy(currentTrait.szTraitValue, pOperand2->szToken);
	    //store both tokens poped in a trait variable to use in atLeastOne function
	    result.bInclude = atLeastOne(pCustomer, &currentTrait);
	    break;
		
	case 1:	//NOTANY
	    strcpy(currentTrait.szTraitType, pOperand1->szToken);
	    strcpy(currentTrait.szTraitValue, pOperand2->szToken);
	    //store both tokens poped in a trait variable to use in notAny function
	    result.bInclude = notAny(pCustomer, &currentTrait);
	    break;
		
	case 2: //ONLY
	    strcpy(currentTrait.szTraitType, pOperand1->szToken);
	    strcpy(currentTrait.szTraitValue, pOperand2->szToken);
	    //store both tokens poped in a trait variable to use in only function
	    result.bInclude = only(pCustomer, &currentTrait);
	    break;
		
	case 3: //AND
	    result.bInclude = and(pOperand1, pOperand2);
	    //call function and if token is AND
	    break;
		
	case 4: //OR
	    result.bInclude = or(pOperand1, pOperand2);
	    //call function or if token is OR
	    break;
    }	
					
    strcpy(result.szBoolean, "Boolean result of ");
    strcat(result.szBoolean, pOperator->szToken);
    //for help in debugging and identifying boolean structs
                  
    return result;
}

/***************************** atLeastOne **************************************
int atLeastOne(Customer *pCustomer, Trait *pTrait)
Purpose:
    Determines whether a customer has a particular trait (type and
    value).  
    If he does, atLeastOne returns TRUE; otherwise, it 
    returns FALSE.
Parameters:
    I Customer pCustomer     One customer structure which also
                             contains traits of that customer.
    I Trait    pTrait        The trait that we want this 
                             customer to have.
Notes:
Return value:
    FALSE - customer didn't have the specified trait
    TRUE - customer did have it
*******************************************************************************/
int atLeastOne(Customer *pCustomer, Trait *pTrait)
{
    if (notAny(pCustomer, pTrait))
    {
        return FALSE;
    }
    return TRUE;
}

/******************************** only *****************************************
int only(Customer *pCustomer, Trait *pTrait)
Purpose:
    Determines whether a customer has a particular trait (type and
    value) and no other trait of the same type. If he does, only 
    returns TRUE; otherwise, it returns FALSE.
Parameters:
    I Customer pCustomer     One customer structure which also
                             contains traits of that customer.
    I Trait    pTrait        The trait that we want this 
                             customer to have.
Notes:
Return value:
    TRUE - customer has the specified trait and no other trait 
    of the same type
    FALSE - customer didn't have the trait and/or had other 
    traits of the same type
*******************************************************************************/
int only(Customer *pCustomer, Trait *pTrait)
{
    if (atLeastOne(pCustomer, pTrait)) //if the customer has the trait
    {
        int i;
        for (i = 0; i < pCustomer->iNumberOfTraits; i++) //go through the customer's trait
        {
            if (strcmp(pCustomer->traitM[i].szTraitType, pTrait->szTraitType) == 0 
                && strcmp(pCustomer->traitM[i].szTraitValue, pTrait->szTraitValue) != 0)
            {
                //if we find a trait of same type but different value
                return FALSE;
            }
        }
        return TRUE;
    }
    return FALSE;
}

/*********************************** and **************************************
int and(Element *pOperand1, Element *pOperand2)
Purpose:
    This function returns the boolean result of the operation AND on 
    two Element variables representing each a boolean.
Parameters:
    I Element *pOperand1		The first of the two boolean Elements.
    I Element *pOperand2		The second of the two boolean Elements.
Notes:
Return value:
    TRUE - operand1 && operand2 = TRUE
    FALSE - operand1 && operand2 = FALSE
*******************************************************************************/
int and(Element *pOperand1, Element *pOperand2)
{
    if (pOperand1->bInclude == TRUE && pOperand2->bInclude == TRUE)
    {
        return TRUE;
    }
    return FALSE;
}

/*********************************** or **************************************
int or(Element *pOperand1, Element *pOperand2)
Purpose:
    This function returns the boolean result of the operation OR on 
    two Element variables representing each a boolean.
Parameters:
    I Element *pOperand1		The first of the two boolean Elements.
    I Element *pOperand2		The second of the two boolean Elements.
Notes:
Return value:
    TRUE - operand1 || operand2 = TRUE
    FALSE - operand1 || operand2 = FALSE
*******************************************************************************/
int or(Element *pOperand1, Element *pOperand2)
{
    if (pOperand1->bInclude == TRUE || pOperand2->bInclude == TRUE)
    {
        return TRUE;
    }
    return FALSE;
}

/**************************** warningExit **************************************
void warningExit(int iWarningCode, QueryResult resultM[], Stack stack)
Purpose:
    This function prints an appropriate error message and readies the 
    program to exit the current querry.
Parameters:
    I int iWarningCode	        The int code to determine the error message.
    O QueryResult resultM[]     Result array to empty.
    O Stack stack		Stack to free.
Notes:
Return value:
    resultM[] parm - Returns an empty array of boolean results for an 
		    invalid query.
    stack parm - Frees the stack for which we have no more use (since 
		this function will be followed by an early return in 
	        the evaluatePostFix function).
*******************************************************************************/
void warningExit(int iWarningCode, QueryResult resultM[], Stack stack)
{
    switch (iWarningCode)
    {
        case WARN_NOT_ENOUGH_OPER:
	    printf("\tWarning: not enough operands in query\n");
	    break;
			
        case WARN_TOO_MANY_OPER:
	    printf("\tWarning: too many operands in query\n");
	    break;
    }
    memset(resultM, 0, sizeof(resultM)); //return an empty array
    freeStack(stack);
}
