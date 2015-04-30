/******************************************************************************
cs2123p5Driver.c by Larry Clark
Purpose:
    This program reads a series	of edges, populates a graph with those edges, 
	calculates the TE and TL for each vertex in the graph, and finally prints 
	the critical path for that graph.
Command Parameters:
    p6 < inputFile
Input:
	Data will contain multiple sets of edges (one set for each graph)
		From	To	PathWeight
		%c		%c		%d
	Each set of edges is terminated by a record having 0 0 0.  
Results:
    For each graph, prints a table containing the vertices, their TE, TL, list 
	of successors, and predecessors. Then prints the critical path(s) for that 
	graph.
Returns:
    0 - normal
    900 - command line argument syntax error
    903 - algorithm error (see message for details)
    503 - bad input data    
Notes:
    This program only allows for a max of 100 vertices and 100 edges per graph.
*******************************************************************************/

// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p6.h"

// dataM has the edges from the data
struct Data dataM[MAX_EDGES];
int main()
{
    int iRun = 0;
    Graph graph;
    while (getGraphData(dataM) == TRUE)
    {
        // Build the graph from the dataM array
        graph = buildGraph(dataM);
        iRun++;
        printGraph(iRun, "Initial", graph);

        // Compute TE and TL
        computePertTEAndTL(graph);
        printGraph(iRun, "PERT TE and TL", graph);

        // Print critical paths
        printCriticalPaths(graph);
        printf("\n");

        // free the graph
        freeGraph(graph);
    }
    return 0;
}
/******************** getGraphData **************************************
  int getGraphData(struct Data dataM[])
Purpose:
    Populates an array of edges with data from stdin.  The array is 
    terminated when EOF or a 0 0 0 is encountered in the data. 
Parameters:
    O   struct Data dataM[]     An array of edges (to, from, path weight)
Notes:
    - The array of edges is terminated by an edge having a from vertex
      equal to the character '0'.
Returns:
    TRUE - data was read to populate the array of vertices.
    FALSE - no data found.
**************************************************************************/
int getGraphData(struct Data dataM[])
{
    char szInput[100];
    int i = 0;
    int iScanfCnt;
    while (fgets(szInput, 50, stdin) != NULL)
    {
        if (i > MAX_EDGES)
            ErrExit(ERR_BAD_INPUT, "too many edges");
        iScanfCnt = sscanf(szInput, "%c %c %d"
            , &dataM[i].cFrom, &dataM[i].cTo, &dataM[i].iPath);
        if (iScanfCnt < 3)
            ErrExit(ERR_BAD_INPUT, " Found: '%s', scanf count is %d", szInput, iScanfCnt);
        if (dataM[i].cFrom == '0')
        {
            dataM[i].cFrom = '\0';
            break;
        }
        i++;
    }
    return i > 0;
}
/******************** newGraph **************************************
    Graph newGraph()
Purpose:
    Allocates a GraphImp and initializes its data.  It returns a
    Graph. 
Parameters:
    n/a
Notes:
    - Uses malloc to allocate a GraphImp.  It also makes certain
      that malloc didn't fail.
    - Initializes iNumvetices to 0.
    - Initializes the array of vertices to zero bytes.
    - 
Returns:
    Graph - the newly allocated graph.
**************************************************************************/
Graph newGraph()
{
    Graph g = (Graph)malloc(sizeof(GraphImp));
    if (g == NULL)
        ErrExit(ERR_ALGORITHM, "malloc for Graph failed");
    g->iNumVertices = 0;
    memset(g->vertexM, '\0',  sizeof(Vertex)*MAX_VERTICES);
    return g;
}
/******************** buildGraph **************************************
    Graph buildGraph(struct Data dataM[])
Purpose:
    Builds a graph from an array of edges.  The Graph is represented by
    an array of vertices and a double adjacency list.
Parameters:
    I   struct Data dataM[]     An array of edges (to, from, path weight)

Notes:
    - The array of edges is terminated by an edge having a from vertex
      equal to the character '0'.
    - Normally, this routine checks to make certain that the input did not
      include a cycle, but since that code wasn't included, the check
      has been commented out.
Returns:
    Graph - the newly allocated and populated graph.
**************************************************************************/
Graph buildGraph(struct Data dataM[])
{
    int i;
    int iFrom;
    int iTo;
    Edge edge;
    Graph graph = newGraph();
    // Initialize the vertex array to zero bytes.
    memset(graph->vertexM, '\0', sizeof(Vertex)*MAX_VERTICES);

    // Go through the array of edges until a From of '\0' is encountered
    for (i = 0; i < MAX_VERTICES; i++)
    {
        if (dataM[i].cFrom == '\0')
            break;
        // Find the From vertex.  searchVertices returns -1 for not found
        iFrom = searchVertices(graph, dataM[i].cFrom);
        if (iFrom == -1)
        {   // not found, so insert the From vertex in the array
            iFrom = graph->iNumVertices;
            graph->iNumVertices++;
            graph->vertexM[iFrom].cLabel = dataM[i].cFrom;
        }
        // Find the To vertex.  searchVertices returns -1 for not found
        iTo = searchVertices(graph, dataM[i].cTo);
        if (iTo == -1)
        {   // not found, so insert the To vertex in the array
            iTo = graph->iNumVertices;
            graph->iNumVertices++;
            graph->vertexM[iTo].cLabel = dataM[i].cTo;
        }
        // insert the edge on both the successor and predecessor lists
        edge.iPath = dataM[i].iPath;
        edge.iVertex = iTo;
        insertOrderedLL(&graph->vertexM[iFrom].successorList, edge);
        edge.iVertex = iFrom;
        insertOrderedLL(&graph->vertexM[iTo].predecessorList, edge);
    }
//    if (!checkCycle(graph))
//        ErrExit(ERR_BAD_INPUT, "Cycle in Graph");
    return graph;
}
/******************** searchVertices **************************************
   int searchVertices(Graph graph, char cVertex)
Purpose:
    Searches the graph's array of vertices for the specified vertex.  If 
    found, it returns the subscript.  If not found, it returns -1.
Parameters:
    I   Graph graph             A directed graph represented by a double
                                adjacency list an an array of vertices.
    I   char cVertex            The vertex's label to be found.
Notes:
    - this just uses a linear search.  It can be greatly improved using
      a binary search (if sorted) or hashing
Returns:
    >= 0 - subscript in the array of vertices if the vertex label is found 
    -1 - not found
**************************************************************************/
int searchVertices(Graph graph, char cVertex)
{
    int i;
    for (i = 0; i < graph->iNumVertices; i++)
    {
        if (cVertex == graph->vertexM[i].cLabel)
            return i;
    }
    return -1;
}
/******************** printGraph **************************************
   void printGraph(int iRun, char *pszSubject, Graph graph)
Purpose:
    Prints a graph which is represensted by a double adjacency list.
    When printing the information about a vertex, it prints the PERT
    TE and TL.  For each vertex, it prints:
        vertex label
        TE
        TL
        predecessors
        successors
Parameters:
    I   int iRun                Identifies which graph is being displayed. 
    I   char *pszSubject        A message to display about this graph.
    I   Graph graph             A directed graph represented by a double
                                adjacency list.  
Notes:
    - Since predecessors and successors are printed on the same line,
      it uses the function printSpaces to help have all the lists of
      predecessors appear in the same column.
Returns:
    n/a
**************************************************************************/
void printGraph(int iRun, char *pszSubject, Graph graph)
{
    int iv;
    EdgeNode *e;
    int iCnt;
    // Print headings
    printf("Graph #%2d: %s\n", iRun, pszSubject);
    printf("%3s %2s %2s\t%-24s    %-24s\n"
        , "Vtx", "TE", "TL", "SUCCESSORS", "PREDECESSORS");
    // for each vertex in the graph
    for (iv = 0; iv < graph->iNumVertices; iv++)
    {
        // print the vertex label, TE, and TL
        printf("%c   %2d %2d\t", graph->vertexM[iv].cLabel
            , graph->vertexM[iv].iMaxFromSource
            , graph->vertexM[iv].iTL);
        iCnt = 0;
        // print each of its successors
        for (e = graph->vertexM[iv].successorList; e != NULL; e = e->pNextEdge)
        {
            iCnt++;
            printf("%c %2d  "
                , graph->vertexM[e->edge.iVertex].cLabel
                , e->edge.iPath);
        }
        // if it didn't have successors, print a "-"
        if (iCnt == 0)
        {
            printf("-     ");
            iCnt = 1;
        }
        // determine the variable-spaced amount for including spaces to get the 
        // predecessor list to print in a specific column
        printSpaces("      ", 4 - iCnt);
        printf("    ");
        iCnt = 0;
        // Print each of its predecessors
        for (e = graph->vertexM[iv].predecessorList; e != NULL; e = e->pNextEdge)
        {
            printf("%c %2d "
                , graph->vertexM[e->edge.iVertex].cLabel
                , e->edge.iPath);
            iCnt++;
        }
        // if it didn't have predecessors, print a "-"
        if (iCnt == 0)
            printf("-");
        printf("\n");
    }
}
/******************** printSpaces **************************************
void printSpaces(char szSpaces[], int iRepeat)
Purpose:
    Prints spaces across a line of output to help with consistent columns.
Parameters:
    I   char szSpaces           A string of spaces to be printed
    I   iRepeat                 The number of times to print that string
                                of spaces.   
Returns:
    n/a
**************************************************************************/
void printSpaces(char szSpaces[], int iRepeat)
{
    int i;
    for (i = 0; i < iRepeat; i++)
    {
        printf("%s", szSpaces);
    }
}

// Linked list manipulation routines used for successor and predecessor lists
// These routines come from the course notes, but were changed slightly 
// for the particular Node and element structures
EdgeNode *searchLL(EdgeNode *pHead, int match, EdgeNode **ppPrecedes)
{
    EdgeNode *p;
    // used when the list is empty or we need to insert at the beginning
    *ppPrecedes = NULL;

    // Traverse through the list looking for where the key belongs or
    // the end of the list.
    for (p = pHead; p != NULL; p = p->pNextEdge)
    {
        if (match == p->edge.iVertex)
            return p;
        if (match < p->edge.iVertex)
            return NULL;
        *ppPrecedes = p;
    }

    // Not found return NULL
    return NULL;
}

EdgeNode *insertOrderedLL(EdgeNode **pHead, Edge value)
{
    EdgeNode *pNew, *pFind, *pPrecedes;
    // see if it already exists
    pFind = searchLL(*pHead, value.iVertex, &pPrecedes);
    if (pFind != NULL)
        return pFind;

    // doesn't already exist.  Allocate a node and insert.
    pNew = allocateEdgeNode(value);

    // Check for inserting at the beginning of the list
    // this will also handle when the list is empty
    if (pPrecedes == NULL)
    {
        pNew->pNextEdge = *pHead;
        *pHead = pNew;
    }
    else
    {
        pNew->pNextEdge = pPrecedes->pNextEdge;
        pPrecedes->pNextEdge = pNew;
    }
    return pNew;
}

EdgeNode *allocateEdgeNode(Edge value)
{
    EdgeNode *pNew;
    pNew = (EdgeNode *)malloc(sizeof(EdgeNode));
    if (pNew == NULL)
        ErrExit(ERR_ALGORITHM, "No available memory for linked list");
    pNew->edge = value;
    pNew->pNextEdge = NULL;
    return pNew;
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
void ErrExit(int iexitRC, char szFmt[], ...)
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
    fprintf(stderr, "p6 \n");
    if (iArg == USAGE_ONLY)
        exit(USAGE_ONLY);
    else
        exit(ERR_COMMAND_LINE);
}