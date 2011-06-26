

#ifndef EXPTREE_H
#define EXPTREE_H

#define VERBOSE

#ifdef VERBOSE
#include <stdio.h>
#endif

#ifndef NULL
#define NULL 0
#endif

#include "Helpers.h"
#include "TreeNodeStack.h"


typedef char ElemType;


/*
 * This is the node type for the tree
 * Here it is important to recognize the StringList declared in every node
 */
struct TreeNode
{
    ElemType    Char;
    int         Digit;
    bool        IsOperator;
    bool        IsDigit;
    
    
    TreeNode* pLeft;
    TreeNode* pRight;

    TreeNode()
    :   Char('0'),
        Digit(0),
        IsOperator(false),
        IsDigit(false),
        pLeft(NULL),
        pRight(NULL)
    {
    }
};


/* This is the main datastructure to handle the tree management,
 * To manage the string lists in every key look at the StringList class
 * in StringList.cc
 */
class ExpTree
{
    TreeNode* mpRoot;

    void        PrintRek(TreeNode* pWalker);
    void        PrintLevelOrder();
    void        DeleteRek(TreeNode* pWalker);
    TreeNode*   GetNode(TreeNode* pWalker, char key);
    TreeNode*   InsertRek(ElemType v, TreeNode * pTreePart);

    void        Mirror(TreeNode* pWalker);

    bool        CharIsOperator(char c);
    bool        CharIsOperand(char c);
    bool        CharIsDigit(char c);

    TreeNode*   EvaluateRek(TreeNode* pTreePart);

    void        CreateInfixExp(TreeNode* pTreePart,
                               int&      rCurStrIdx,
                               char*     pString);

    public:
    
    ExpTree();
    ~ExpTree();
    
    void    InsertExp(char* pString);
    void    Mirror();
    void    EvaluateTree();
    void    GetInfixExp(char* pString);
    

    void    Print();
};


/* Node structre for the Queue
 */
struct QueueNode
{
    QueueNode* pNext;
    TreeNode* pData;
    
    QueueNode()
    :   pNext(NULL),
        pData(NULL)
    {
    }
};


/* class for managing the Queue
 *
 * the queue is needed to print a tree in level order
 */
class Queue
{
    QueueNode* mpHead;
    QueueNode* mpTail;

    public:

    Queue();
    //~Queue_t();

    bool        Enqueue(TreeNode* pN);
    TreeNode*   Dequeue();

    bool        IsEmpty() {return (mpHead == NULL);};
};

#endif
