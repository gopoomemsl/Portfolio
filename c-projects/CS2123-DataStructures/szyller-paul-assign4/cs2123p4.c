/******************************************************************************
cs2123p3.c by Paul Szyller
Purpose:
	This program runs a simulation to compare machine improvement proposals 
	on a server processing widgets through two steps. The program can be run 
	to simulate two different proposed process alternative and the current 
	process. For each alternative, stats are calculated and printed, as well 
	as an optional verbose mode to print each events through the simulation.
Command Parameters:
	Alternative to run the simulation for:
		-aC : current server processing
		-aA : alternative A
		-aB : alternative B
	Additional switch:
		-v : verbose mode
Input:
	The standard input file is in the following format:
		lWidgetNr	iStep1tu	iStep2tu	iArrivalDelta
			%ld			%d			%d			%d
	The input comes from a text file rather than being randomly generated 
	in the program to allow for output consistency through the class.
	Alternative B will use a different input file to allow for the faster 
	step 1 times.
Results:
	Prints a header indicating the process alternative choosen.
	Prints a table of all the events as they occur through the simulation 
	if verbose mode has been activated.
	Prints the following stats for the simulation:
		Number of widgets processed
		Average time in system (from arrival to completion at step 2)
		Average queue time step 1
		Average queue time step 2 (not produced for Alternative B or current)
Returns:
	0 - normal
	900 - command line argument syntax error
	903 - algorithm error (see message for details)
	503 - bad input
Notes:
	This program has a time limit of 1000 time units for the simulation.
*******************************************************************************/



/***          ***/
/*** Includes ***/
/***          ***/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "cs2123p4.h"
/******************************************************************************
cs2123p4.h
Purpose: 
	Header file for this program.
Notes:
	This is a header file provided by Professor Clark.
*******************************************************************************/



/***           ***/
/*** Constants ***/
/***           ***/

#define AC_INPUT		"p4ACinput.txt" //input file name for altA and Current
#define B_INPUT			"p4Binput.txt"	//input file name for altB
#define TIME_LIMIT		10000			//simulation time limit



/***                                        ***/
/*** Prototypes Not Included in Header File ***/
/***                                        ***/

//Main Simulation Functions
void processCommandSwitches(int argc, char *argv[], int *pbVerbose, char *pcRunType);

//Simulation Prep Functions
LinkedList newListFromInput();
Simulation newSim(LinkedList eventList, int bVerbose, char cRunType);
Server newServer(char *pszServerNm);

//Simulation Event Functions
void arrival(Simulation sim, Widget *pWidget);
void queueUp(Simulation sim, Widget *pWidget, Queue queue);
void seize(Simulation sim, Queue queue, Server server);
void release(Simulation sim, Queue queue, Server server);
void leaveSystem(Simulation sim, Widget *pWidget);

//Print Functions
void printHeader (Simulation sim);
void printFooter (Simulation sim, Queue queue1, Queue queue2);
void printEvent(Simulation sim, char szFmt[], ... );

//Free Functions
void freeSim(Simulation sim);
void freeServersAndQueues(Simulation sim, Server s1, Server s2, Queue q1, Queue q2);
void freeQueue(Queue queue);
void freeList(LinkedList list);



/***                  ***/
/*** Global Variables ***/
/***                  ***/

FILE *pInputFile;



/***                           ***/
/*** Main Simulation Functions ***/
/***                           ***/

/********************************* main ****************************************
int main (int argc, char *argv[])
Purpose:
	This the main functions of the program, it calls the command switch 
	processing function to register the alternative choosen and wether 
	verbose mode has been choosen or not, it creates the LinkedList and 
	Simulation, calls the appropriate functions to populate both, then 
	calls the function to run the simulation and to free all of our allocs.
Parameters:
	I	int argc		Number of command line argument.
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
	//command switches
	int bVerbose;
	char cRunType;
	processCommandSwitches(argc, argv, &bVerbose, &cRunType);
	
	//create the simulation
	LinkedList list;
	Simulation sim;
	list = newListFromInput();
	sim = newSim(list, bVerbose, cRunType);

	//run the simulation and terminate
	runSimulation(sim, TIME_LIMIT);
	freeSim(sim);
	fclose(pInputFile);
	return 0;	
}

/**************************** runSimulation ************************************
void runSimulation(Simulation sim, int iTimeLimit)
Purpose:
	Goes through a list of events in a Simulation and run them as they are 
	encountered.
Parameters:
	I	Simulation sim		The simulation variable containing the list of 
							events.
	I	int iTimeLimit		A time limit upon which the simulation will terminate 
							if it is reached before all of the events are ran.
Returns:
Notes:
*******************************************************************************/
void runSimulation(Simulation sim, int iTimeLimit)
{	
	//Variables
	Event event;
	Server server1, server2;
	Queue queue1, queue2;
	
	//create servers and queues
	server1 = newServer("Server 1");
	queue1 = newQueue("Queue 1");
	if (sim->cRunType == 'A')
	{
		server2 = newServer("Server 2");
		queue2 = newQueue("Queue 2");	
	}

	//begin simulation
	printHeader(sim);
	while (removeLL(sim->eventList, &event)) 
	{	
		if (event.iTime > iTimeLimit)
		{
			printFooter(sim, queue1, queue2);	
			freeServersAndQueues(sim, server1, server2, queue1, queue2);	
			ErrExit(ERR_BAD_INPUT, "Event time (%d) is out of simulation bounds (%d)\n", 
					event.iTime, iTimeLimit);
		}

		sim->iClock = event.iTime;
		switch (event.iEventType)
		{
			case EVT_ARRIVAL:
				arrival(sim, &event.widget);
				queueUp(sim, &event.widget, queue1);
				seize(sim, queue1, server1);
				break;

			case EVT_SERVER1_COMPLETE:
				release(sim, queue1, server1);
				if (sim->cRunType == 'A') //Alternative A follows up with server 2
				{
					queueUp(sim, &event.widget, queue2);
					seize(sim, queue2, server2);
				}
				else //Alternative B and Current leave after server 1
				{
					leaveSystem(sim, &event.widget);
				}
				break;

			case EVT_SERVER2_COMPLETE:
				release(sim, queue2, server2);
				leaveSystem(sim, &event.widget);
				break;
		
			default:
				ErrExit(ERR_ALGORITHM, "Unknown event type: %d\n", event.iEventType);
		}
	}
	
	printFooter(sim, queue1, queue2);	
	freeServersAndQueues(sim, server1, server2, queue1, queue2);	
}



/***                           ***/
/*** Simulation Prep Functions ***/
/***                           ***/

/********************** processCommandSwitches *********************************
void processCommandSwitches(int argc, char *argv[], int *pbVerbose, char *pcRunType)
Purpose:
	Checks the syntax of command line arguments and returns the alternative 
	choosen and the boolean determining if verbose mode is activated.  
	If any switches are unknown, it exits with an error.
Parameters:
	I	int argc			Count of command line arguments.
	I	char *argv[]		Array of command line arguments.
	O	int *pVerbose		Was verbose mode activated?
	O	char *pcRunType		Alternative choosen.
Notes:
	If a -? switch is passed, the usage is printed and the program exits
	with USAGE_ONLY.
	If a syntax error is encountered (e.g., unknown switch), the program
	prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
*******************************************************************************/
void processCommandSwitches(int argc, char *argv[], int *pbVerbose, char *pcRunType)
{
	char *pszInputFileNm = NULL;
	*pbVerbose = FALSE;
	
	int i;
	for (i = 1; i < argc; i++) 
	//goes through the command line arguments after the file name
	{
		if (argv[i][0] != '-') //if the argument isn't a switch, send error
		{
			exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
		}
	
		switch (argv[i][1])
		{
			case 'v': //-v verbose mode
				*pbVerbose = TRUE;
				break;
	
			case 'a': //-aA, -aB, -aC alternatives switches
				switch (argv[i][2])
				{
					case 'A':
						*pcRunType = 'A';
						pszInputFileNm = AC_INPUT;
						break;
	
					case 'B':
						*pcRunType = 'B';
						pszInputFileNm = B_INPUT;
						break;
	
					case 'C':
						*pcRunType = 'C';
						pszInputFileNm = AC_INPUT;
						break;
	
					default:
						exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
				}
				break;
	
			default:
				exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
		}
	}

	if (pszInputFileNm == NULL)
	{
		exitUsage(USAGE_ERR, ERR_MISSING_SWITCH, "-aA, -aB, or -aC");
	}

	pInputFile = fopen(pszInputFileNm, "r");
	if (pInputFile == NULL)
	{
		exitUsage(USAGE_ERR, "Input file not found ", pszInputFileNm);
	}
}

/*************************** newListFromInput **********************************
LinkedList newListFromInput()
Purpose:
	Goes through the input file, for each line, creates a widget and an 
	arrival event for that widget and insert it in a list.
Parameters:
Returns:
	Functionally:
		A LinkedList variable populated from the input.
Notes:
*******************************************************************************/
LinkedList newListFromInput()
{
	/***variables***/
	char szInputBuffer[MAX_LINE_SIZE + 1];
	Widget widget;
	Event arrival;
	LinkedList list;
	int iClock, iNextArrival, iScanfCnt;
	
	//allocate list
	list = newLinkedList();
	
	iClock = 0; 
	while (fgets(szInputBuffer, MAX_LINE_SIZE, pInputFile) != NULL 
			&& iClock <= MAX_ARRIVAL_TIME) //for each line of the input file
	{	
		if (szInputBuffer[0] == '\n') //if line is empty, ignore
		{
			continue;
		}
	
		//populate the widget variable with data from input line and current clock
		iScanfCnt = sscanf(szInputBuffer, "%ld %d %d %d\n", &(widget.lWidgetNr), 
							&(widget.iStep1tu), &(widget.iStep2tu), &iNextArrival);
		widget.iArrivalTime = iClock;
	
		if (iScanfCnt < 4) //if there's less than 4 tokens in the line
		{
			ErrExit(ERR_BAD_INPUT, "%sExpected 4 tokens,received %d successful values\n",
					szInputBuffer, iScanfCnt);
			continue;
		}
	
		if (widget.iStep1tu < 0 || widget.iStep2tu < 0 || iNextArrival < 0)
		//if the values are negative values
		{
			ErrExit(ERR_BAD_INPUT, 
					"%sStep1tu, Step2tu, and DeltaArrival cannot be negative values.\n",
					szInputBuffer, iScanfCnt);
			continue;
		}
	
		//populate the arrival Event variable
		arrival.iEventType = EVT_ARRIVAL;
		arrival.iTime = iClock;
		arrival.widget = widget;
		//insert it into the list
		insertOrderedLL(list, arrival);
		//increment clock for next input line (next widget)
		iClock += iNextArrival;
	}
	
	return list;
}

/********************************* newSim **************************************
Simulation newSim(LinkedList eventList, int bVerbose, char cRunType)
Purpose:
	Creates a new Simulation variable with a clock set to 0, and a list 
	of event passed by argument.
Parameters:
	I	LinkedList eventList	The list of events in the simulation.
	I	bVerbose				Is the simulation run in verbose mode?
	I	cRunType				Alternative to run the simulation for.
Returns:
	Functionally:
		A Simulation variable containing the list of event passed in.
Notes:
*******************************************************************************/
Simulation newSim(LinkedList eventList, int bVerbose, char cRunType)
{
	Simulation sim = (Simulation) malloc(sizeof(SimulationImp));
	sim->iClock = 0;
	sim->bVerbose = bVerbose;
	sim->lSystemTimeSum = 0;
	sim->lWidgetCount = 0;
	sim->cRunType = cRunType;
	sim->eventList = eventList;
	return sim;
}

/***************************** newServer ***************************************
Server newServer(char *pszServerNm)
Purpose:
	Creates a new Server variable with the passed String as a name and 
	initializes it to be marked as not busy.
Parameters:
	I	char *pszServerNm		The name to give this new Server.
Returns:
	Functionally:
		A new Server variable.
Notes:
*******************************************************************************/
Server newServer(char *pszServerNm)
{
	Server s = (Server)malloc(sizeof(ServerImp));
	s->bBusy = FALSE;
	strcpy(s->szServerName, pszServerNm);
	return s;
}



/***                            ***/
/*** Simulation Event Functions ***/
/***                            ***/

/****************************** arrival ****************************************
void arrival(Simulation sim, Widget *pWidget)
Purpose:
	Handles the arrival event for a given widget.
	In this case, just print if verbose mode is activated.
Parameters:
	I	Simulation sim		Simulation running the event.
	I	Widget *pWidget		Current widget.
Returns:
Notes:
*******************************************************************************/
void arrival(Simulation sim, Widget *pWidget)
{
	printEvent(sim, " %6d %8ld %s", sim->iClock, pWidget->lWidgetNr, "Arrived");
}

/******************************* queueUp ***************************************
void queueUp(Simulation sim, Widget *pWidget, Queue queue)
Purpose:
	Handles the queueUp event for a given widget.
	In this case, create a new queue element, insert the current widget 
	and queueing time in said element, and insert the element in the given 
	queue.
	This function also increment the widget count of the queue and prints 
	the event if verbose mode was activated.
Parameters:
	I	Simulation sim		Simulation running the event.
	I	Widget *pWidget		Current widget.
	O	Queue queue			Queue to insert the widget in.
Returns:
	queue parm - the queue the widget was inserted in.
Notes:
*******************************************************************************/
void queueUp(Simulation sim, Widget *pWidget, Queue queue)
{
	//populate a QElement variable with the current widget and the current time
	QElement element;
	element.widget = *pWidget;
	element.iEnterQTime = sim->iClock;
	//insert the element in the queue
	insertQ(queue, element);
	//increment the queue count
	queue->lQueueWidgetTotalCount++;
	
	printEvent(sim, " %6d %8ld %s %s", sim->iClock, pWidget->lWidgetNr, "Enter", 
				queue->szQName);
}

/****************************** seize ******************************************
void seize(Simulation sim, Queue queue, Server server)
Purpose:
	Handles the seize event for a given server.
	In this case, take the top element out of the given queue while updating 
	the queue stats, insert the widget in the given server and mark the server 
	busy, and insert a new event in the simulation's event list representing 
	the widget exiting the server.
	This function also prints the different steps of the event if verbose 
	mode was activated.
Parameters:
	I	Simulation sim		Simulation running the event.
	I/O	Queue queue			Queue to remove the widget from.
	I/O	Server server		Server to insert the widget in, also the 
							server to give its name to the newly created 
							server completion event.
Returns:
	queue parm - the queue to remove the widget from.
	server parm - the server to insert the widget in.
Notes:
*******************************************************************************/
void seize(Simulation sim, Queue queue, Server server)
{
	if (server->bBusy == FALSE && queue->pHead != NULL) 
	//if server is free and there's something in the queue
	{
		//take top element out of queue and add its wait time to the sum
		QElement element;
		removeQ(queue, &element);
		long lQWaitTime = sim->iClock - element.iEnterQTime;
		queue->lQueueWaitSum += lQWaitTime;
	
		printEvent(sim, " %6d %8ld %s %s%s %ld", sim->iClock, element.widget.lWidgetNr,
					"Leave", queue->szQName, ", waited", lQWaitTime);
	
		//put widget taken out of queue into the server and mark it busy
		server->widget = element.widget;
		server->bBusy = TRUE;
	
		printEvent(sim, " %6d %8ld %s %s", sim->iClock, element.widget.lWidgetNr, 
					"Seized", server->szServerName);
	
		//create a SERVER_COMPLETE event for the widget and place it into the event list
		Event event;
		event.widget = server->widget;
		if (strcmp(server->szServerName, "Server 1") == 0)
		{
			if (sim->cRunType == 'A')
			{
				//altA only spends step1 in server 1
				event.iTime = sim->iClock + event.widget.iStep1tu;
			}
			else
			{
				//altB and current spend both step 1 and step 2 in server 1
				event.iTime = sim->iClock + event.widget.iStep1tu + event.widget.iStep2tu;
			}
			event.iEventType = EVT_SERVER1_COMPLETE;
		}
		if (strcmp(server->szServerName, "Server 2") == 0)
		{
			event.iTime = sim->iClock + event.widget.iStep2tu;
			event.iEventType = EVT_SERVER2_COMPLETE;
		}

		insertOrderedLL(sim->eventList, event);
	}
}

/******************************** release **************************************
void release(Simulation sim, Queue queue, Server server)
Purpose:
	Handles the release event for a given server.
	In this case, just mark the server as not busy and attempt to seize a 
	new widget from the queue.
	This function also prints the event if verbose mode was activated.
Parameters:
	I	Simulation sim		Simulation running the event.
	I	Queue queue			Queue to seize from.
	O	Server server		Server to release the widget from.
Returns:
	server parm - server made available again.
Notes:
*******************************************************************************/
void release(Simulation sim, Queue queue, Server server)
{
	printEvent(sim, " %6d %8ld %s %s", sim->iClock, server->widget.lWidgetNr, 
				"Released", server->szServerName);
	
	//mark the server free
	server->bBusy = FALSE;
	//attempt to seize a new widget for the server
	seize(sim, queue, server);
}

/**************************** leaveSystem **************************************
void leaveSystem(Simulation sim, Widget *pWidget)
Purpose:
	Handles the leaveSystem event for a given widget.
	In this case, just update the stats in the simulation.
	This function also prints the event if verbose mode was activated.
Parameters:
	I	Simulation sim		Simulation running the event.
	I	Widget *pWidget		The widget exiting the server.
Returns:
Notes:
*******************************************************************************/
void leaveSystem(Simulation sim, Widget *pWidget)
{
	//update the time sum and widget count with the exiting widget
	long lTimeInSys = sim->iClock - pWidget->iArrivalTime;
	sim->lSystemTimeSum += lTimeInSys;
	sim->lWidgetCount++;
	
	printEvent(sim, " %6d %8ld %s %ld", sim->iClock, pWidget->lWidgetNr, 
				"Exit System, in system", lTimeInSys);
}



/***                 ***/
/*** Print Functions ***/
/***                 ***/

/*************************** printHeader ***************************************
void printHeader(Simulation sim)
Purpose:
	This function prints a header announcing which process is being used 
	and a header to the event table if verbose mode was activated.
Parameters:
	I	Simulation sim		Contains the cRunType and bVerbose variables.
Returns:
Notes:
*******************************************************************************/
void printHeader (Simulation sim)
{
	//simulation header
	printf("\n");
	switch (sim->cRunType)
	{
		case 'A':
			printf("\tSimulation for Alternative A\n");
			break;
			
		case 'B':
			printf("\tSimulation for Alternative B\n");
			break;
			
		case 'C':
			printf("\tSimulation for Current\n");
			break;
	}
	
	//verbose-only events header
	printEvent(sim, "\n %6s %8s %s", "Time", "Widget", "Event");
}

/***************************** printFooter *************************************
void printFooter(Simulation sim, Queue queue1, Queue queue2)
Purpose:
	This function prints a footer event if verbose mode was activated, 
	then prints the stats for the simulation.
Parameters:
	I	Simulation sim		Contains the cRunType and bVerbose 
							variables, and the stats of the simulation.
	I	Queue queue1		Contains the queue1 stats.
	I	Queue queue2		Contains the queue2 stats.
Returns:
Notes:
*******************************************************************************/
void printFooter (Simulation sim, Queue queue1, Queue queue2)
{
	//verbose-only terminating event
	switch (sim->cRunType)
	{
		case 'A':
			printEvent(sim, " %6d          %s", sim->iClock, 
						"Simulation Complete for Alternative A");
			break;

		case 'B':
			printEvent(sim, " %6d          %s", sim->iClock, 
						"Simulation Complete for Alternative B");
			break;
			
		case 'C':
			printEvent(sim, " %6d          %s", sim->iClock, 
						"Simulation Complete for Current");
			break;
	}
	
	//calculate and print stats
	printf("\n");	
	long lWidgetCount = sim->lWidgetCount;
	printf("\t%-31s = %8ld\n", "Number of Widgets processed", lWidgetCount);	
	double dAvgQ1 = (double)(queue1->lQueueWaitSum) / queue1->lQueueWidgetTotalCount;
	printf("\t%-31s = %8.1lf\n", "Average Queue Time for Server 1", dAvgQ1);	
	if (sim->cRunType == 'A')
	{
		double dAvgQ2 = (double)(queue2->lQueueWaitSum) / queue2->lQueueWidgetTotalCount;
		printf("\t%-31s = %8.1lf\n", "Average Queue Time for Server 2", dAvgQ2);
	}	
	double dAvgInSys = (double)(sim->lSystemTimeSum) / sim->lWidgetCount;
	printf("\t%-31s = %8.1lf\n", "Average Time in System", dAvgInSys);	
	printf("\n");
}

/****************************** printEvent *************************************
void printEvent(Simulation sim, char szFmt[], ... )
Purpose:
	If verbose mode was activated, prints an event defined by the printf-like 
	szFmt and the corresponding arguments to that function.  The number of 
	arguments after szFmt varies dependent on the format codes in szFmt.
Parameters:
	I	Simulation sim		Contains the bVerbose boolean.
	I	char szFmt[]		This contains the message to be printed
							and format codes (just like printf) for 
							values that we want to print.
	I	...					A variable-number of additional arguments
							which correspond to what is needed
							by the format codes in szFmt. 
Returns:
Notes:
	Requires including <stdarg.h>
*******************************************************************************/
void printEvent(Simulation sim, char szFmt[], ... )
{
	if (sim->bVerbose == TRUE)
	{
		va_list args;               
		va_start(args, szFmt);      
		vprintf(szFmt, args);                  
		va_end(args);
		printf("\n");
	}
}



/***                ***/
/*** Free Functions ***/
/***                ***/

/******************************* freeSim ***************************************
void freeSim(Simulation sim)
Purpose:
	This is a free function for a given Simulation variable.
Parameters:
	O	Simulation sim		Simulation to free.
Returns:
	sim parm - freed Simulation.
Notes:
*******************************************************************************/
void freeSim(Simulation sim)
{
	freeList(sim->eventList);
	free(sim);
}

/************************* freeServersAndQueues ********************************
void freeServersAndQueues(Simulation sim, Server s1, Server s2, Queue q1, Queue q2)
Purpose:
	This is a free function for the queues and servers used through 
	the simulation.
Parameters:
	I	Simulation sim		Contains the cRunType variables.
	O	Server s1			Server 1 to free.
	O	Server s2			Server 2 to free.
	O	Queue q1			Queue 1 to free.
	O	Queue q2			Queue 2 to free.
Returns:
	s1 parm - freed Server.
	s2 parm - freed Server.
	q1 parm - freed Queue.
	q2 parm - freed Queue.
Notes:
*******************************************************************************/
void freeServersAndQueues(Simulation sim, Server s1, Server s2, Queue q1, Queue q2)
{
	freeQueue(q1);
	free(s1);	
	if (sim->cRunType == 'A')
	{
		freeQueue(q2);
		free(s2);
	}
}

/******************************* freeQueue *************************************
void freeQueue(Queue queue)
Purpose:
	This is a free function for a given Queue variable.
Parameters:
	O	Queue queue		Queue to free.
Returns:
	queue parm - freed Queue.
Notes:
*******************************************************************************/
void freeQueue(Queue queue)
{
	NodeQ *p = queue->pHead;
	while (p != NULL)
	{
		NodeQ *pFree = p;
		p = p->pNext;
		free(pFree);
	}
	free(queue);
}

/******************************** freeList *************************************
void freeList(LinkedList list)
Purpose:
	This is a free function for a given LinkedList variable.
Parameters:
	O	LinkedList list		LinkedList to free.
Returns:
	list parm - freed LinkedList.
Notes:
*******************************************************************************/
void freeList(LinkedList list)
{
	NodeLL *p = list->pHead;
	while (p != NULL)
	{
		NodeLL *pFree = p;
		p = p->pNext;
		free(pFree);
	}
	free(list);
}



/***                       ***/
/*** Linked List Functions ***/
/***                       ***/

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
	I	LinkedList list		The current list.
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



/***                 ***/
/*** Queue Functions ***/
/***                 ***/

/*************************** removeQ *******************************************
int removeQ(Queue queue, QElement *pFromQElement)
Purpose:
	Removes the element in the front of the queue and returns its element.
Parameters:
	I/O	Queue queue					The queue to remove the element from.
	O	QElement *pFromQElement		The QElement variable to store the 
									removed element in.
Returns:
	Functionally:
		Boolean representing the success of the removal:
		TRUE - success
		FALSE - queue is empty		
	pFromQElement parm - the variable to store the removed element in.
Notes:
*******************************************************************************/
int removeQ(Queue queue, QElement *pFromQElement)
{
	NodeQ *p;
	if (queue->pHead == NULL)
	{
		return FALSE;
	}
	p = queue->pHead;
	*pFromQElement = p->element;
	queue->pHead = p->pNext;
	if (queue->pHead == NULL)
	{
		queue->pFoot = NULL;
	}
	free(p);
	return TRUE;
}

/**************************** insertQ ******************************************
void insertQ(Queue queue, QElement element)
Purpose:
	Inserts an element in the queue.
Parameters:
	O	Queue queue			The queue to insert the element in.
	I	QElement element	The element to be inserted in the queue.
Returns:
	queue parm - the queue with the new element added.
Notes:
*******************************************************************************/
void insertQ(Queue queue, QElement element)
{
	NodeQ *pNew;
	pNew = allocNodeQ(queue, element);
	if (queue->pFoot == NULL)
	{
		queue->pFoot = pNew;
		queue->pHead = pNew;
	}
	else
	{
		queue->pFoot->pNext = pNew;
		queue->pFoot = pNew;
	}
}

/****************************** allocNodeQ *************************************
NodeQ *allocNodeQ(Queue queue, QElement value)
Purpose:
	Creates and allocate the memory for a new node including the passed by value.
Parameters:
	I	Queue queue			The current queue.
	I	QElement value		The element to be included in the new node.
Returns:
	Functionally:
		A pointer to the new node containing the element we passed it.
Notes:
*******************************************************************************/
NodeQ *allocNodeQ(Queue queue, QElement value)
{
	NodeQ *pNew;
	pNew = (NodeQ *)malloc(sizeof(NodeQ));
	if (pNew == NULL)
	{
		ErrExit(ERR_ALGORITHM, "No available memory for queue");
	}
	pNew->element = value;
	pNew->pNext = NULL;
	return pNew;
}

/******************************** newQueue *************************************
Queue newQueue(char szQueueNm[])
Purpose:
	Creates and allocates the memory for a new Queue.
Parameters:
	I	char szQueue	Nm[]The new queue's name.
Returns:
	Functionally:
		The newly created queue.
Notes:
*******************************************************************************/
Queue newQueue(char szQueueNm[])
{
	Queue q = (Queue)malloc(sizeof(QueueImp));
	q->pHead = NULL;
	q->pFoot = NULL;
	q->lQueueWaitSum = 0;
	q->lQueueWidgetTotalCount = 0;
	strcpy(q->szQName, szQueueNm);
	return q;
}



/***                           ***/
/*** Utility Routines Provided ***/
/***                           ***/

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
	I	int iArg					command argument subscript or control:
										> 0 - command argument subscript
										0 - USAGE_ONLY - show usage only
										-1 - USAGE_ERR - show message and usage
	I	char *pszMessage			error message to print
	I	char *pszDiagnosticInfo		supplemental diagnostic information
Returns:
Notes:
	This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
	switch (iArg)
	{
		case USAGE_ERR:
			fprintf(stderr, "Error: %s %s\n", pszMessage, pszDiagnosticInfo);
			break;

		case USAGE_ONLY:
			break;

		default:
			fprintf(stderr, "Error: bad argument #%d.  %s %s\n", iArg, 
					pszMessage, pszDiagnosticInfo);
	}
	// print the usage information for any type of command line error
	fprintf(stderr, "p4 -aA -v\n");
	if (iArg == USAGE_ONLY)
		exit(USAGE_ONLY); 
	else 
		exit(ERR_COMMAND_LINE);
}

/******************** ErrExit **************************************
void ErrExit(int iexitRC, char szFmt[], ... )
Purpose:
	Prints an error message defined by the printf-like szFmt and the
	corresponding arguments to that function.  The number of 
	arguments after szFmt varies dependent on the format codes in
	szFmt.  
	It also exits the program with the specified exit return code.
Parameters:
	I	int iexitRC		Exit return code for the program
	I	char szFmt[]	This contains the message to be printed
						and format codes (just like printf) for 
						values that we want to print.
	I	...				A variable-number of additional arguments
						which correspond to what is needed
						by the format codes in szFmt. 
Returns:
	Returns a program exit return code:  the value of iexitRC.
Notes:
	- Prints "ERROR: " followed by the formatted error message specified 
		in szFmt. 
	- Prints the file path and file name of the program having the error.
		This is the file that contains this routine.
	- Requires including <stdarg.h>
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

/******************** getToken **************************************
char * getToken (char *pszInputTxt, char szToken[], int iTokenSize)
Purpose:
	Examines the input text to return the next token.  It also
	returns the position in the text after that token.  This function
	does not skip over white space, but it assumes the input uses 
	spaces to separate tokens.
Parameters:
	I	char *pszInputTxt	input buffer to be parsed
	O	char szToken[]		Returned token.
	I	int iTokenSize		The size of the token variable. This is 
							used to prevent overwriting memory. The 
							size should be the memory size minus 1 
							(for the zero byte).
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
		ErrExit(ERR_ALGORITHM, "getToken passed a NULL pointer");

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
