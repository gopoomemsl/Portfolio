/******************************************************************************
cs2123p5.c by Paul Szyller
Purpose:
    This file is part of a larger program which goals it is to read a 
    command data file to create a diagnosis tree as well as run additional 
    commands utilizing the created tree.
Command Parameters:
    n/a (see cs2123p5Driver.c)
Input:
    The input comes from the driver file and is described in said file.
    (see cs2123p5Driver.c)
Results:
    This file handles the insert, searchT, allocateNodeT, freeT, prettyPrintT, 
    help, and deleteNode.
Returns:
    The returns are handled in the driver where the main function is and are 
    therefore described there.
    (see cs2123p5Driver.c)
Notes:
    This program only contains the functions required for assignment 5.
    Other parts of the code are contained in the cs2123p5Driver.c file.
*******************************************************************************/



/***          ***/
/*** Includes ***/
/***          ***/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"
/******************************************************************************
cs2123p5.h
Purpose: 
    Header file for this program.
Notes:
    This is a header file provided by Professor Clark.
*******************************************************************************/



/***           ***/
/*** Functions ***/
/***           ***/

/********************************* insert **************************************
void insert(NodeT *p, char *szParentId, Element elem, char cYN)
Purpose:
    This function inserts a diagnosis or question after the provided parent, 
    the side (left or right) of the insert depends on the cYN provided.
Parameters:
    I	NodeT *p            The current node the function is on to look for the parent node. 
                            On the original function call this should be the root of the tree.
    I	char *szParentId    The parent node to insert the diagnosis or question after.
    I	Element elem        The diagnosis or question to insert.
    I	char cYN            The answer to the parent node to determine the side of insertion.
Returns:
Notes:
    This function is recursive.
*******************************************************************************/
void insert(NodeT *p, char *szParentId, Element elem, char cYN)
{
    NodeT *pParent;
    NodeT *pInsert;

    //if root is missing
    if (p == NULL)
    {
        printf("\t*** Warning:  Unable to insert, root is missing\n");
        return;
    }

    //look for a version of the node already in the tree
    pInsert = searchT(p, elem.szId);
    //if the node is already there
    if (pInsert != NULL)
    {
        printf("\t*** Warning:  Node %s already exists in the tree\n", elem.szId);
        return;
    }
	
    //look for parent node
    pParent = searchT(p, szParentId);
    //if parent node was not found
    if (pParent == NULL)
    {
        printf("\t*** Warning:  Unable to insert, parent node is missing\n");
        return;
    }

    //allocate new node
    pInsert = allocateNodeT(elem);
	
    //if the answer to parent node was Y
    if (cYN == 'Y')
    {
        //if there already is a node at that location
        if (pParent->pRight != NULL)
        {
            printf("\t*** Warning:  An answer has already been provided for the parent Node\n");
            return;
        }
        //else insert there
        pParent->pRight = pInsert;
    }
	
    //if the answer to parent node was N
    else
    {
        //if there already is a node at that location
        if (pParent->pLeft != NULL)
        {
            printf("\t*** Warning:  An answer has already been provided for the parent Node\n");
            return;
        }
        //else insert there
        pParent->pLeft = pInsert;
    }
}

/****************************** searchT ****************************************
NodeT *searchT(NodeT *p, char *szId)
Purpose:
    This function searches through the tree to find the node with the provided ID.
Parameters:
    I	NodeT *p        The current node the function is on. On the original function 
                        call this should be the node to start the search at.
    I	char *szId      The ID for the node to locate.
Returns:
    Functionally:
        A pointer to the node corresponding to the given ID.
Notes:
    This function is recursive.
*******************************************************************************/
NodeT *searchT(NodeT *p, char *szId)
{
    NodeT *pResult;

    //if the tree is empty or we reach the end of a branch
    if (p == NULL)
    {
        return NULL;
    }
	
    //if the desired element has been found
    if (strcmp(p->element.szId, szId) == 0)
    {
        return p;
    }
	
    //else go left first
    pResult = searchT(p->pLeft, szId);
    //if the node was not found on the left side
    if (pResult == NULL)
    {
        //then go right
        pResult = searchT(p->pRight, szId);
    }

    return pResult;
}

/************************** allocateNodeT **************************************
NodeT *allocateNodeT(Element elem)
Purpose:
    This function allocates memory for a node containing the given element.
Parameters:
    I	Element elem	The element to be contained in the newly allocated node.
Returns:
    Functionally:
        A pointer to the newly allocated node.
Notes:
*******************************************************************************/
NodeT *allocateNodeT(Element elem)
{
    NodeT *p;
    p = (NodeT *)malloc(sizeof(NodeT));
    if (p == NULL)
    {
        ErrExit(ERR_ALGORITHM, "No available memory for tree");
    }
    p->element = elem;
    p->pLeft = NULL;
    p->pRight = NULL;
    return p;
}

/******************************** freeT ****************************************
void freeT(NodeT *p)
Purpose:
    This function frees the tree or subtree starting with the provided node as its root.
Parameters:
    I/O	NodeT *p        The current node the function is on. On the original function 
                        call this should be the root of the tree to delete.
Returns:
    p parm - the freed tree node.
Notes:
    This function is recursive.
*******************************************************************************/
void freeT(NodeT *p)
{
    //if tree is already empty at the target node 
    if (p == NULL)
    {
        return;
    }
	
    //if we reached a leaf
    if (p->pLeft == NULL && p->pRight == NULL)
    {
        //free and go back up
        free(p);
        return;
    }
	
    //else go left
    freeT(p->pLeft);
    //done with the left side, go right
    freeT(p->pRight);
}

/****************************** prettyPrintT ***********************************
void prettyPrintT(NodeT *p, int iIndent, TextList textList)
Purpose:
    This function prints the tree starting with the node provided in a formatted way.
Parameters:
    I	NodeT *p                The current node the function is on. On the original 
                                function call this should be the root of the tree 
                                to print.
    I	int iIdent              The indent for the line printed by the current call 
                                of the function.
    I	TextList textList       The list where the text for each node is stored.
Returns:
Notes:
    This function is recursive.
*******************************************************************************/
void prettyPrintT(NodeT *p, int iIndent, TextList textList)
{
    int i;
	
    //if tree is empty, simply return
    if (p == NULL)
    {
        return;
    }
	
    //visit the right side first since it will be on top of the print
    prettyPrintT(p->pRight, iIndent + 1, textList);
	
    //visit the current node (print at desired indent)
    printf("\n");
    for (i = 0; i < iIndent; i++)
    {
        printf("\t");
    }
    printf("%s %s", p->element.szId, getText(textList, p->element.szId));
	
    //visit the left side which will be on the botton of the print
    prettyPrintT(p->pLeft, iIndent + 1, textList);
}

/*************************** help **********************************************
char *help(NodeT *p, char *szAnswers, int iAns, TextList textList)
Purpose:
    This function goes through the diagnosis tree with the answer list 
    provided and returns the resulting diagnosis.
Parameters:
    I	NodeT *p                The current node the function is on. On the original function 
                                call this should be the root of the tree.
    I	char *szAnswers         The string of Y or N answers
    I	int iAns                The index in the string of answers of the current answer.
    I	TextList textList       The list where the text for each node is stored.
Returns:
    Functionally:
        A string representing the ID of the resulting diagnosis.
Notes:
    This function is recursive.
*******************************************************************************/
char *help(NodeT *p, char *szAnswers, int iAns, TextList textList)
{
    //if tree is empty
    if (p == NULL)
    {
        return NULL;
    }
	
    //if we have reached a diagnosis, return the diagnosis id
    if (p->element.cNodeType == 'D')
    {
        return p->element.szId;
    }
	
    //else, print the current node
    printf("\t%s: %s ", p->element.szId, getText(textList, p->element.szId));
	
    //if there's no more answers in the list before getting to a diagnosis
    if(!(szAnswers[iAns]))
    {
        printf("\t*** Warning:  Not enough answers to reach a diagnosis\n");
    }
	
    //if the current answer in the list is N
    if (szAnswers[iAns] == 'N')
    {
        printf("N\n");
        return help(p->pLeft, szAnswers, ++iAns, textList);
    }
	
    //if the current answer in the list is Y
    if (szAnswers[iAns] == 'Y')
    {
        printf("Y\n");
        return help(p->pRight, szAnswers, ++iAns, textList);
    }
	
    return NULL;
}

/************************ deleteNode *******************************************
void deleteNode(NodeT *p, char *szId)
Purpose:
	This function is called to delete a node from the tree. Its parents will no 
	longer reference it and all of it will be freed along with all of its descendants.
Parameters:
	I/O	NodeT *p		The current node the function is on. On the original function 
						call this should be the root of the tree.
	I	char *szId		The ID of the node to delete.
Returns:
	p parm - the tree modified to no longer contain the desired node.
Notes:
	This function is recursive.
*******************************************************************************/
void deleteNode(NodeT *p, char *szId)
{
    NodeT *pRemove;
	
    //if the tree is empty or we reached the end of a branch
    if (p == NULL)
    {
        return;
    }
	
    //if the node to be deleted is one of the current node's children
    //on the left
    if (p->pLeft != NULL && strcmp(p->pLeft->element.szId, szId) == 0)
    {
        pRemove = p->pLeft;
        p->pLeft = NULL; //the parent will no longer reference the node
        freeT(pRemove); //free the node and all of its descendants
        return;
    }
    //on the right
    if (p->pRight != NULL && strcmp(p->pRight->element.szId, szId) == 0)
    {
        pRemove = p->pRight;
        p->pRight = NULL; //the parent will no longer reference the node
        freeT(pRemove); //free the node and all of its descendants
        return;
    }
	
    //go left
    deleteNode(p->pLeft, szId);
    //go right
    deleteNode(p->pRight, szId);
}
