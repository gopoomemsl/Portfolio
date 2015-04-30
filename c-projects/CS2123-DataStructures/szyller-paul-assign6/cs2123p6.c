/******************************************************************************
cs2123p6.c by Paul Szyller
Purpose:
    This file is part of a larger program which goals it is to read a series 
    of edges, populate a graph with those edges, calculate the TE and TL for 
    each vertex in the graph, and finally print the critical path for that 
    graph.
Command Parameters:
    n/a (see cs2123p6Driver.c)
Input:
    The input comes from the driver file and is described in said file.
    (see cs2123p6Driver.c)
Results:
    This file handles calculation for the TE and TL for each vertex. This file 
    is also responsible for finding and printing the critical path of the graph.
Returns:
    The returns are handled in the driver where the main function is and are 
    therefore described there.
    (see cs2123p6Driver.c)
Notes:
    This program only contains the functions required for assignment 6.
    Other parts of the code are contained in the cs2123p6Driver.c file.
*******************************************************************************/



/***          ***/
/*** Includes ***/
/***          ***/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p6.h"
/******************************************************************************
cs2123p6.h
Purpose: 
    Header file for this program.
Notes:
    This is a header file provided by Professor Clark.
*******************************************************************************/



/***                                        ***/
/*** Prototypes Not Included in Header File ***/
/***                                        ***/

void computeMaxFromSource(Graph g, int iVertex, int iPathLength);
void computeMaxFromSink(Graph g, int iVertex, int iPathLength);
int findMaxTE(Graph g);
void computeTL(Graph g, int iMaxTE);
void findCriticalPath(Graph g, int iVertex, char* szCriticalPath, int iPathIndex);
void freeList(EdgeNode* p);



/***           ***/
/*** Functions ***/
/***           ***/

/************************** computePertTEAndTL *********************************
void computePertTEAndTL(Graph graph)
Purpose:
    This function calculates the TE and TL for each vertex in a given graph.
    The TE and TL for each vertex are stored in the vertices themselves.
Parameters:
    I/O	Graph graph     The graph to compute the TE and TL from.
Returns:
    graph parm - the updated Graph variable.
Notes: 
*******************************************************************************/
void computePertTEAndTL(Graph graph)
{
    int i, iMaxTE, iPathLength = 0;
	
    //set iMaxFromSource and iMaxFromSink to 0 for each vertex
    for (i = 0; i < graph->iNumVertices; i++)
    {
        graph->vertexM[i].iMaxFromSource = 0;
        graph->vertexM[i].iMaxFromSink = 0;
    }
	
    //calculate iMaxFromSource (TE) and iMaxFromSink for each vertex
    for (i = 0; i < graph->iNumVertices; i++)
    //for each vertex
    {
        if (graph->vertexM[i].predecessorList == NULL)
        //if vertex is a source
        {
            computeMaxFromSource(graph, i, iPathLength);
            //compute max distance from current vertex to each successor
        }
		
        if (graph->vertexM[i].successorList == NULL)
        //if vertex is a sink
        {
            computeMaxFromSink(graph, i, iPathLength);
            //compute max distance from current vertex to each predecessor
        }
    }
	
    //compute max TE of the graph
    iMaxTE = findMaxTE(graph);
	
    //compute TL for each vertex
    computeTL(graph, iMaxTE);
}

/*********************** computeMaxFromSource **********************************
void computeMaxFromSource(Graph g, int iVertex, int iPathLength)
Purpose:
    This function calculates the max distance from a source (or TE) for 
    each vertex starting from a given source.
Parameters:
    I/O	Graph g             The graph to compute the TE from.
    I	int iVertex         The index for the current vertex the function 
                            is working on.
    I	int iPathLength     The length of the current path to the current 
                            vertex.
Returns:
    g parm - the updated Graph variable.
Notes:
    This function is recursive.
*******************************************************************************/
void computeMaxFromSource(Graph g, int iVertex, int iPathLength)
{	
    EdgeNode* p;
    int iNewPathLength;

    //set p to point at the first successor
    p = g->vertexM[iVertex].successorList;
    while (p != NULL)
    //go through each successor
    {	
        //add the current edge's weight to the length of the current path
        iNewPathLength = iPathLength + p->edge.iPath;
        //if the new path length calculate is greater than the current 
        //iMaxFromSource for the vertex
        if (iNewPathLength > g->vertexM[p->edge.iVertex].iMaxFromSource)
        {
            //set the new path length to be the iMaxFromSource for the vertex
            g->vertexM[p->edge.iVertex].iMaxFromSource = iNewPathLength;
            //go look at the successor's successors
            computeMaxFromSource(g, p->edge.iVertex, iNewPathLength);
        }
        //next successor
        p = p->pNextEdge;
    }
}

/************************* computeMaxFromSink **********************************
void computeMaxFromSink(Graph g, int iVertex, int iPathLength)
Purpose:
    This function calculates the max distance from a sink for each vertex 
    starting from a given sink.
Parameters:
    I/O	Graph g             The graph to compute the distance from.
    I	int iVertex         The index for the current vertex the function 
                            is working on.
    I	int iPathLength     The length of the current path to the current 
                            vertex.
Returns:
    g parm - the updated Graph variable.
Notes:
    1. This function is recursive.
    2. This function works the same way as computeMaxFromSource does.
*******************************************************************************/
void computeMaxFromSink(Graph g, int iVertex, int iPathLength)
{
    EdgeNode* p;
    int iNewPathLength;
	
    p = g->vertexM[iVertex].predecessorList;
    while (p != NULL)
    {		
        iNewPathLength = iPathLength + p->edge.iPath;
        if (iNewPathLength > g->vertexM[p->edge.iVertex].iMaxFromSink)
        {
            g->vertexM[p->edge.iVertex].iMaxFromSink = iNewPathLength;
            computeMaxFromSink(g, p->edge.iVertex, iNewPathLength);
        }
        p = p->pNextEdge;
    }
}

/****************************** findMaxTE **************************************
int findMaxTE(Graph g)
Purpose:
    This function goes through the vertices in the graph to find the 
    max TE among the vertices.
Parameters:
    I	Graph g     The graph to compute the max TE from.
Returns:
    Functionally:
        An integer representing the max TE for the graph.
Notes:
*******************************************************************************/
int findMaxTE(Graph g)
{
    int i, iMaxTE = 0;
    //go through each vertex
    for (i = 0; i < g->iNumVertices; i++)
    {
        if (g->vertexM[i].iMaxFromSource > iMaxTE)
        //if the current vertex's TE is greater than the max
        {
            //change the max to be the current vertex's TE
            iMaxTE = g->vertexM[i].iMaxFromSource;
        }
    }
    return iMaxTE;
}

/************************** computeTL ******************************************
void computeTL(Graph g, int iMaxTE)
Purpose:
    This function calculates the TL for each vertex from its previously 
    calculated TE and max distance from a sink.
Parameters:
    I/O	Graph g         The graph to compute the TL from.
    I	int iMaxTE      The previously calculated max TE for the graph.
Returns:
    g parm - the updated Graph variable.
Notes:
*******************************************************************************/
void computeTL(Graph g, int iMaxTE)
{
    int i;
    //for each vertex
    for (i = 0; i < g->iNumVertices; i++)
    {
        //TL = Max TE - max distance from sink
        g->vertexM[i].iTL = iMaxTE - g->vertexM[i].iMaxFromSink;
    }
}

/*************************** printCriticalPaths ********************************
void printCriticalPaths(Graph g)
Purpose:
    This function finds and prints (with the help of the function 
    findCriticalPath) the critical path(s) for the graph, using the 
    previously calculated TE and TL for each vertex.
Parameters:
    I	Graph g     The graph to print the critical path from.
Returns:
Notes:
*******************************************************************************/
void printCriticalPaths(Graph g)
{
    char szCriticalPath[MAX_EDGES];
    int i;

    //header for the critical path(s)
    printf("Critical Path(s)\n");
    //for each vertex
    for (i = 0; i < g->iNumVertices; i++)
    {
        if (g->vertexM[i].predecessorList == NULL && 
            g->vertexM[i].iMaxFromSource == g->vertexM[i].iTL)
        //if current vertex is a source and is part of a critical path
        {
            findCriticalPath(g, i, szCriticalPath, 0);
            //start the recursive search for more points in the critical path 
            //starting with the current vertex as the source
        }
    }
}

/************************ findCriticalPath *************************************
void findCriticalPath(Graph g, int iVertex, char* szCriticalPath, int iPathIndex)
Purpose:
    This function finds and prints (with the help of the function 
    printCriticalPaths) the critical path(s) for the graph, using 
    the previously calculated TE and TL for each vertex.
Parameters:
    I	Graph g                 The graph to print the critical path from.
    I	int iVertex             The index for the current vertex the function 
                                is working on.
    I/O	char* szCriticalPath    The string variable holding the critical path 
                                in progress.
    I	int iPathIndex          The current index in the szCriticalPath string 
                                where the next vertex should be inserted.
Returns:
    szCriticalPath parm - the critical path in progress.
Notes:
    This function is recursive.
*******************************************************************************/
void findCriticalPath(Graph g, int iVertex, char* szCriticalPath, int iPathIndex)
{	
    if (g->vertexM[iVertex].iMaxFromSource == g->vertexM[iVertex].iTL)
    //if the current vertex is part of a critical path
    {
        //add the label for the current vertex to the critical path string
        szCriticalPath[iPathIndex] = g->vertexM[iVertex].cLabel;
        //followed by a space
        szCriticalPath[iPathIndex + 1] = ' ';
	
        //set p to point to the first successor
        EdgeNode* p = g->vertexM[iVertex].successorList;
	
        if (p == NULL)
        //if the current vertex is a sink
        {
            szCriticalPath[iPathIndex + 2] = '\0';
            //end the criticalpath string
            printf("%s\n", szCriticalPath);
            //print it
        }
	
        while (p != NULL)
        //go through each successor
        {
            findCriticalPath(g, p->edge.iVertex, szCriticalPath, iPathIndex + 2);
            //find the next points on the critical path
            p = p->pNextEdge;
            //next successor
        }
    }
}

/********************************* freeGraph ***********************************
void freeGraph(Graph graph)
Purpose:
    This function simply frees the graph and the successor and predecessor 
    lists for each vertex.
Parameters:
    I/O	Graph graph     The graph to free.
Returns:
    graph parm - the newly freed graph.
Notes:
*******************************************************************************/
void freeGraph(Graph graph)
{
    int i;
    EdgeNode* p;
	
    for (i = 0; i < graph->iNumVertices; i++)
    {
        p = graph->vertexM[i].successorList;
        freeList(p);		
        p = graph->vertexM[i].predecessorList;
        freeList(p);
    }
	
    free(graph);
}

/****************************** freeList ***************************************
void freeList(EdgeNode* p)
Purpose:
    This function simply frees the given linked list.
Parameters:
    I/O	EdgeNode* p     The list to free.
Returns:
    p parm - the newly freed list.
Notes:
*******************************************************************************/
void freeList(EdgeNode* p)
{
    EdgeNode* pFree;
    while (p != NULL)
    {
        pFree = p;
        p = p->pNextEdge;
        free(pFree);
    }
}
