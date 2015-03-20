/******************************************************************************
cs2123p3.c by Paul Szyller
Purpose:
    This program reads a list of statements, each describing 
    a person, the time before departure for that person, and 
    the difference between this person's and the next person's 
    arrival.
Command Parameters:
    n/a
Input:
    The standard input file stream contains records in the following format:
		szName	iDeltaDepart	iDeltaNextArrival
		 11s	    3d		          3d
    Some sample data:
        Fred   10 5
		Daphne 4 3
		Velma  6 6
		Shaggy 9 6
		Scooby 2 5
		Scrappy 1 3
Results:
    Prints an ordered formatted list of the events.
    For each person in the input file: 
        - create an arrival and a departure event
        - place the events in an ordered linked list
    Once every event is in the list, goes through it and print them 
    in a table format
Returns:
    0 - normal
    900 - command line argument syntax error
    903 - algorithm error (see message for details)
    503 - bad input
Notes:
    This program has a time limit of 1000 time units for the simulation.
*******************************************************************************/



/*** Includes ***/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "cs2123p3.h"
/******************************************************************************
cs2123p3.h
Purpose: 
    Header file for this program.
Notes:
    This is a header file provided by Professor Clark.
*******************************************************************************/



/*** Prototypes for additional functions ***/

LinkedList newListFromInput();
Simulation newSim(LinkedList eventList);
void runSimulation(Simulation simulation, int iTimeLimit);
void runStartEvent();
void runEvent(Event event);
void runEndEvent();
void freeSim(Simulation sim);



/*** Functions ***/

/********************************* main ***************************************
int main (int argc, char *argv[])
Purpose:
    This the main functions of the program, it creates the LinkedList and 
    Simulation, calls the appropriate functions to populate both, then calls
    the function to run the simulation and to free all of our allocs.
Parameters:
    I   int argc		Number of command line argument.
    I	char *argv[]	Command line arguments.
Returns:
    Functionally:
        Integer representing the success of the operation or error encountered.
        0 - normal
		900 - command line argument syntax error
		903 - algorithm error (see message for details)
		503 - bad input
Notes: 
*******************************************************************************/
int main(int argc, char *argv[])
{
	//setting up the variables
	LinkedList list;
	Simulation sim;
	
	//initializing the simulation
	list = newListFromInput();
	sim = newSim(list);
	
	//the actual simulation
	runSimulation(sim, 1000);
	
	//frees everything
	freeSim(sim);
	return 0;	
}

/*********************** newListFromInput **************************************
LinkedList newListFromInput()
Purpose:
    Takes in the input file, create a Person and 2 Event variables per line 
	and populates a LinkedList with said events.
Parameters:
Returns:
    Functionally:
        A LinkedList variable populated from the input.
Notes:
*******************************************************************************/
LinkedList newListFromInput()
{
	/***variables***/
	char szInputBuffer[100];
	Person person;
	Event arrival, departure;
	LinkedList list;
	int iClock, iNextArrival, iScanfCnt;
	
	//set up a new list
	list = newLinkedList();
	
	iClock = 0; //the clock time for the next arrival
	while (fgets(szInputBuffer, 100, stdin) != NULL) //goes through the file line by line
	{	
		//if the line is empty, just ignore it
		if (szInputBuffer[0] == '\n')
		{
			continue;
		}
		
		//counts the tokens in the line and place them in their desired variables
		iScanfCnt = sscanf(szInputBuffer, "%s %d %d\n", person.szName, 
			&person.iDepartUnits, &iNextArrival);
			
		//if the line had less than 3 tokens, print the line, a warning,
		//and go to the next line
		if (iScanfCnt < 3)
		{
			ErrExit(ERR_BAD_INPUT, "%sExpected Name, DeltaDepart, and DeltaNextArrival,received %d successful values\n",
			 szInputBuffer, iScanfCnt);
			continue;
		}
		
		//if the DeltaDepart or DeltaNextArrival are negative values, print 
		//the line, a warning, and go to the next line
		if (person.iDepartUnits < 0 || iNextArrival < 0)
		{
			ErrExit(ERR_BAD_INPUT, "%sDeltaDepart and DeltaNextArrival cannot be negative values.\n",
			 szInputBuffer, iScanfCnt);
			continue;
		}
		
		//create the arrival event for the current person/line
		arrival.iEventType = EVT_ARRIVE;
		arrival.iTime = iClock;
		arrival.person = person;
		
		//create the departure event
		departure.iEventType = EVT_DEPART;
		departure.iTime = iClock + person.iDepartUnits;
		departure.person = person;
		
		//insert both events in the list
		insertOrderedLL(list, arrival);
		insertOrderedLL(list, departure);
		
		//increment clock to correspond to the next arrival time
		iClock += iNextArrival;
	}
	return list;
}

/****************************** newSim ****************************************
Simulation newSim(LinkedList eventList)
Purpose:
    Creates a new Simulation variable with a clock set to 0 and a list 
	of event passed by argument.
Parameters:
    I   LinkedList eventList	The list of events in the simulation.
Returns:
    Functionally:
        A Simulation variable containing the list of event passed in.
Notes:
*******************************************************************************/
Simulation newSim(LinkedList eventList)
{
	//allocate the memory
	Simulation sim = (Simulation) malloc(sizeof(SimulationImp));
	sim->iClock = 0; //set clock to 0
	sim->eventList = eventList; //insert list in the simulation
	return sim;
}

/*************************** runSimulation ************************************
void runSimulation(Simulation sim, int iTimeLimit)
Purpose:
    Goes through a list of events in a Simulation and run them as they are encountered.
Parameters:
    I   Simulation sim		The simulation variable containing the list of events.
	I	int iTimeLimit		A time limit upon which the simulation will terminate 
							if it is reached before all of the events are ran.
Returns:
Notes:
*******************************************************************************/
void runSimulation(Simulation sim, int iTimeLimit)
{	
	Event event;
	
	runStartEvent(); //in this case just prints a header
	//removes the events from the list one by one while placing them in the current event variable
	while (removeLL(sim->eventList, &event)) 
	{
		if (event.iTime > iTimeLimit) 
		//if the current event is over the time limit, terminate the simulation and send error
		{
			runEndEvent(sim->iClock);
			ErrExit(ERR_BAD_INPUT, "Event time (%d) is out of simulation bounds (%d)\n",
			 event.iTime, iTimeLimit);
		}		
		sim->iClock = event.iTime; //set simulation clock to current event clock
		runEvent(event); //in this case just prints the event
	}
	runEndEvent(sim->iClock); //in this case just prints a termination event
}

/************************** runStartEvent *************************************
void runStartEvent()
Purpose:
    This will run the appropriate starting event before the actual 
	simulation. In this case it just prints a header to the table.
Parameters:
Returns:
Notes: 
    This function and the other 2 runEvent functions were created for better 
	modularity. This way the runSimulation function can be kept and one would 
	only have to modify the 3 runEvent functions.
*******************************************************************************/
void runStartEvent()
{
	printf("%-5s\t%-11s\t%-11s\n", "Time", "Person", "Event");
}

/***************************** runEvent ***************************************
void runEvent(Event event)
Purpose:
    This will execute the appropriate action for the current event.
	In this case it just prints the event in a formatted way.
Parameters:
	I	Event event		The current event to execute.
Returns:
Notes: 
    This function and the other 2 runEvent functions were created for better 
	modularity. This way the runSimulation function can be kept and one would 
	only have to modify the 3 runEvent functions.
*******************************************************************************/
void runEvent(Event event)
{
	switch (event.iEventType)
	{
		case EVT_ARRIVE:
			printf("%5d\t%-11s\t%-11s\n", event.iTime, event.person.szName, "Arrive");
			break;
			
		case EVT_DEPART:
			printf("%5d\t%-11s\t%-11s\n", event.iTime, event.person.szName, "Depart");
			break;
		
		default:
			ErrExit(ERR_ALGORITHM, "Unknown event type: %d\n", event.iEventType);
	}
}

/**************************** runEndEvent **************************************
void runEndEvent(int iEventTime)
Purpose:
    This will run the appropriate ending event after the actual 
	simulation. In this case it just prints a SIMULATION TERMINATE event.
Parameters:
	I	int iEventTime		The time of the last event in the simulation.
Returns:
Notes: 
    This function and the other 2 runEvent functions were created for better 
	modularity. This way the runSimulation function can be kept and one would 
	only have to modify the 3 runEvent functions.
*******************************************************************************/
void runEndEvent(int iEventTime)
{
	printf("%5d\t%-11s\t%-11s\n", iEventTime, "SIMULATION", "TERMINATES");
}

/**************************** freeSim ******************************************
void freeSim(Simulation sim)
Purpose:
    Frees the Simulation and all of the allocs associated with it.
Parameters:
    I   Simulation sim		The Simulation variable to free.
Returns:
    sim parm - the freed Simulation variable.
Notes:
*******************************************************************************/
void freeSim(Simulation sim)
{
	NodeLL *p = sim->eventList->pHead;
	while (p != NULL)
	{
		NodeLL *pFree = p;
		p = p->pNext;
		free(pFree);
	}
	free(sim->eventList);
	free(sim);
}



/*** Linked List Functions ***/

/**************************** removeLL *****************************************
int removeLL(LinkedList list, Event *pValue)
Purpose:
    Removes the node in the front of the list and returns its element.
Parameters:
    I/O	LinkedList list		The list to remove the element from.
	O	Event *pValue		The Event variable to store the removed element in.
Returns:
    Functionally:
        Boolean representing the success of the removal:
		TRUE - success
		FALSE - list is empty		
    pValue parm - the variable to store the removed element in.
Notes: 
    Adapted for a LinkedList with Header Node.
*******************************************************************************/
int removeLL(LinkedList list, Event *pValue)
{
	NodeLL *pRemove;
	if (list->pHead->pNext == NULL)
	{
		return FALSE;
	}
	*pValue = list->pHead->pNext->event;
	pRemove = list->pHead->pNext;
	list->pHead->pNext = list->pHead->pNext->pNext;
	free(pRemove);
	return TRUE;
}

/************************ insertOrderedLL **************************************
NodeLL *insertOrderedLL(LinkedList list, Event value)
Purpose:
    Inserts an element in the list in the correct ordered position.
Parameters:
    O	LinkedList list		The list to insert the event in.
	I	Event value			The Event to be inserted in the list.
Returns:
    Functionally:
        A pointer to the newly created node containing the element.
    list parm - the list with the new element added.
Notes: 
    Adapted for a LinkedList with Header Node.
*******************************************************************************/
NodeLL *insertOrderedLL(LinkedList list, Event value)
{
	NodeLL *pNew, *pPrecedes;
	searchLL(list, value.iTime, &pPrecedes);
	pNew = allocateNodeLL(list, value);
	pNew->pNext = pPrecedes->pNext;
	pPrecedes->pNext = pNew;
	return pNew;
}

/**************************** searchLL *****************************************
NodeLL *searchLL(LinkedList list, int match, NodeLL **ppPrecedes)
Purpose:
    Searches a list for a key match, returns a pointer to the node found 
	or NULL if it wasn't found in the list, also returns a pointer to the 
	preceding node via the parameters.
Parameters:
    I	LinkedList list			The list to search through.
	I	int match				The key match to be found.
	O	NodeLL **ppPrecedes		A pointer to the node preceding the correct 
								location of the key in the list.
Returns:
    Functionally:
        A pointer to the node with the matching key or NULL.
    ppPrecedes parm - a pointer to the node preceding the location where 
					the key is if it exists or should be if it doesn't.
Notes: 
    Adapted for a LinkedList with Header Node.
*******************************************************************************/
NodeLL *searchLL(LinkedList list, int match, NodeLL **ppPrecedes)
{
	NodeLL *p;
	*ppPrecedes = list->pHead;
	for (p = list->pHead->pNext; p != NULL; p = p->pNext)
	{
		if (match == p->event.iTime)
		{
			return p;
		}
		if (match < p->event.iTime)
		{
			return NULL;
		}
		*ppPrecedes = p;
	}	
	return NULL;
}

/************************* newLinkedList ***************************************
LinkedList newLinkedList()
Purpose:
    Creates and allocates the memory for a new LinkedList with Header Node.
Parameters:
Returns:
    Functionally:
        The newly created list.
Notes: 
    Adapted for a LinkedList with Header Node.
*******************************************************************************/
LinkedList newLinkedList()
{
	LinkedList list = (LinkedList) malloc(sizeof(LinkedListImp));
	if (list == NULL)
	{
		ErrExit(ERR_ALGORITHM, "No available memory for linked list");
	}
	NodeLL *pHeader = (NodeLL *) malloc(sizeof(NodeLL));
	list->pHead = pHeader;
	list->pHead->pNext = NULL;
	return list;
}

/************************* allocateNodeLL **************************************
NodeLL *allocateNodeLL(LinkedList list, Event value)
Purpose:
    Creates and allocate the memory for a new node including the passed by event.
Parameters:
    I   LinkedList list		The current list.
	I	Event value			The element to be included in the new node.
Returns:
    Functionally:
        A pointer to the new node containing the element we passed it.
Notes:
*******************************************************************************/
NodeLL *allocateNodeLL(LinkedList list, Event value)
{
	NodeLL *pNew = (NodeLL *) malloc(sizeof(NodeLL));
	if (pNew == NULL)
	{
		ErrExit(ERR_ALGORITHM, "No available memory for linked list");
	}
	pNew->event = value;
	pNew->pNext = NULL;
	return pNew;
}



/***  Utility Routines Provided ***/

/******************** ErrExit **************************************
  void ErrExit(int iexitRC, char szFmt[], ... )
Purpose:
    Prints an error message defined by the printf-like szFmt and the
    corresponding arguments to that function.  The number of 
    arguments after szFmt varies dependent on the format codes in
    szFmt.  
    It also exits the program with the specified exit return code.
Parameters:
    I   int iexitRC             Exit return code for the program
    I   char szFmt[]            This contains the message to be printed
                                and format codes (just like printf) for 
                                values that we want to print.
    I   ...                     A variable-number of additional arguments
                                which correspond to what is needed
                                by the format codes in szFmt. 
Notes:
    - Prints "ERROR: " followed by the formatted error message specified 
      in szFmt. 
    - Prints the file path and file name of the program having the error.
      This is the file that contains this routine.
    - Requires including <stdarg.h>
Returns:
    Returns a program exit return code:  the value of iexitRC.
**************************************************************************/
void ErrExit(int iexitRC, char szFmt[], ... )
{
    va_list args;               // This is the standard C variable argument list type
    va_start(args, szFmt);      // This tells the compiler where the variable arguments
                                // begins.  They begin after szFmt.
    printf("ERROR: ");
    vprintf(szFmt, args);       // vprintf receives a printf format string and  a
                                // va_list argument
    va_end(args);               // let the C environment know we are finished with the
                                // va_list argument
    printf("\n");
    exit(iexitRC);
}

/******************** exitUsage *****************************
    void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    In general, this routine optionally prints error messages and diagnostics.
    It also prints usage information.

    If this is an argument error (iArg >= 0), it prints a formatted message 
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits 
    with ERR_COMMAND_LINE.

    If this is a usage error (but not specific to the argument), it prints 
    the specific message and its supplemental diagnostic information.  It 
    also shows the usage and exist with ERR_COMMAND_LINE. 

    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript or control:
                                    > 0 - command argument subscript
                                    0 - USAGE_ONLY - show usage only
                                    -1 - USAGE_ERR - show message and usage
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
    switch (iArg)
    {
        case USAGE_ERR:
            fprintf(stderr, "Error: %s %s\n"
                , pszMessage
                , pszDiagnosticInfo);
            break;
        case USAGE_ONLY:
            break;
        default:
            fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
                , iArg
                , pszMessage
                , pszDiagnosticInfo);
    }
    // print the usage information for any type of command line error
    fprintf(stderr, "p3 < inputFile.txt\n");
    if (iArg == USAGE_ONLY)
        exit(USAGE_ONLY); 
    else 
        exit(ERR_COMMAND_LINE);
}

/******************** getToken **************************************
char * getToken (char *pszInputTxt, char szToken[], int iTokenSize)
Purpose:
    Examines the input text to return the next token.  It also
    returns the position in the text after that token.  This function
    does not skip over white space, but it assumes the input uses 
    spaces to separate tokens.
Parameters:
    I   char *pszInputTxt       input buffer to be parsed
    O   char szToken[]          Returned token.
    I   int iTokenSize          The size of the token variable.  This is used
                                to prevent overwriting memory.  The size
                                should be the memory size minus 1 (for
                                the zero byte).
Returns:
    Functionally:
        Pointer to the next character following the delimiter after the token.
        NULL - no token found.
    szToken parm - the returned token.  If not found, it will be an
        empty string.
Notes:
    - If the token is larger than the szToken parm, we return a truncated value.
    - If a token isn't found, szToken is set to an empty string
    - This function does not skip over white space occurring prior to the token.
**************************************************************************/
char * getToken(char *pszInputTxt, char szToken[], int iTokenSize)
{
    int iDelimPos;                      // found position of delim
    int iCopy;                          // number of characters to copy
    char szDelims[20] = " \n\r";        // delimiters
    szToken[0] = '\0';

    // check for NULL pointer 
    if (pszInputTxt == NULL)
        ErrExit(ERR_ALGORITHM
        , "getToken passed a NULL pointer");

    // Check for no token if at zero byte
    if (*pszInputTxt == '\0')
        return NULL;

    // get the position of the first delim
    iDelimPos = strcspn(pszInputTxt, szDelims);

    // if the delim position is at the first character, return no token.
    if (iDelimPos == 0)
        return NULL;

    // see if we have more characters than target token, if so, trunc
    if (iDelimPos > iTokenSize)
        iCopy = iTokenSize;             // truncated size
    else
        iCopy = iDelimPos;

    // copy the token into the target token variable
    memcpy(szToken, pszInputTxt, iCopy);
    szToken[iCopy] = '\0';              // null terminate

    // advance the position
    pszInputTxt += iDelimPos;
    if (*pszInputTxt == '\0')
        return pszInputTxt;
    else
        return pszInputTxt + 1;
}
