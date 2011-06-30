
#include "ExpTree.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/* constructor for the queue
 */
Queue::Queue()
:   mpHead(NULL),
    mpTail(NULL)
{
}


/* constructor for the binary tree
 */
ExpTree::ExpTree()
:   mpRoot(NULL)
{
}


/* rec function for deletion
 *
 * this method is called by the destructor to use
 * recusion
 *
 * @param a TreeNode pointer to traverse the tree
 */
void ExpTree::DeleteRek(TreeNode* pWalker)
{
    if (pWalker != NULL)
    {
        DeleteRek(pWalker->pLeft);
        DeleteRek(pWalker->pRight);
        delete pWalker;
    }
}


/* destructor for the binary tree, we need post order traversal
 */
ExpTree::~ExpTree()
{
    DeleteRek(mpRoot);
}


/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/

/* enqueue a TreeNode* pointer
 */
bool Queue::Enqueue(TreeNode* pN)
{
    QueueNode* pOldTail = mpTail;
    mpTail = new QueueNode;
    if (mpTail == NULL)
        return false;

    mpTail->pData = pN;
    
    if (mpHead == NULL)
        mpHead = mpTail;
    else
        pOldTail->pNext = mpTail;

    return true;
}


/* dequeue a TreeNode* pointer
 */
TreeNode* Queue::Dequeue()
{
    if (mpHead == NULL)
        return NULL;
    else
    {
        TreeNode* pRet = mpHead->pData;
        QueueNode* pDel = mpHead;
        
        mpHead = mpHead->pNext;

        delete pDel;
        return pRet;
    }
}


/* Exercise 1: this method inserts a expression in the binary tree.
 *
 * The algorithm uses two stacks one for internal and another for
 * leaf nodes. The trick here is, if we have processed a closing bracket
 * we push the operator to the "wrong" stack
 *
 * detailed:
 *
 * iterate through the string:
 *     - if we find a opening bracket, just continue
 *     - if we find an operand push it to the leaf stack 
 *       here we take care of numbers with more than digits
 *     - if we find an operator push it to the internal_stack
 *     - if we find a closing bracket magic happens
 *       we pop the from internal_stack, then we pop the first
 *       child from the leaf_stack which have to be the right child
 *       of the current popped operator. After that we pop the next
 *       object from the leaf_stack wich will be the left child.
 *       Now we push the operator tree node on the LEAF STACK!!.
 *       So next time it is popped, it is treated like an operand.
 *
 * This algorithm works with "TreeNode"s only because the connections
 * between the nodes have to be persistent. In Addition to this, it is
 * neccessary that we have comletete paranthesized expression.
 *
 * @param a string
 */
void ExpTree::InsertExp(char *pString)
{
    TreeNodeStack internal_stack;
    TreeNodeStack leaf_stack;
    int i;
    TreeNode* p_temp;
    
    for (i = 0; i < Helpers::StringLen(pString); i++)
    {
        char cur_c = pString[i];
        
        if (cur_c == '(')
            continue;
        /* if we find an operand */
        else if (CharIsOperand(cur_c))
        {
            p_temp = new TreeNode;
            if (CharIsDigit(cur_c))
            {
                /* convert char to int */
                p_temp->Digit = (int)cur_c - 48;
                p_temp->IsDigit = true;
            }
            else
            {
                p_temp->Char = cur_c;
                p_temp->IsDigit = false;
            }

            p_temp->IsOperator = false;

            leaf_stack.Push(p_temp);

            /* take care of numbers with more than one digit */
            if (p_temp->IsDigit)
            {
                int k;
                for (k = i + 1; k < Helpers::StringLen(pString); k++)
                {
                    if (CharIsDigit(pString[k]))
                    {
                        TreeNode* prev_node;
                        int cur_digit = (int)pString[k] - 48;
                        
                        leaf_stack.Pop(&prev_node);

                        prev_node->Digit = prev_node->Digit * 10 + cur_digit;

                        leaf_stack.Push(prev_node);

                        i++;
                    }
                    else
                        break;
                }
            }
                
        }
        /* if we find an operator */
        else if (CharIsOperator(cur_c))
        {
            p_temp = new TreeNode;
            p_temp->Char = cur_c;
            p_temp->IsDigit = false;
            p_temp->IsOperator = true;
            internal_stack.Push(p_temp);
        }
        /* if we find a closing bracket */
        else if (cur_c == ')')
        {
            internal_stack.Pop(&p_temp);
            leaf_stack.Pop(&(p_temp->pRight));
            leaf_stack.Pop(&(p_temp->pLeft));

            leaf_stack.Push(p_temp);
        }
    }

    mpRoot = p_temp;
}


/* this method mirrors a tree on the vertical axis
 *
 * method is only a caller for the recursive function
 */
void ExpTree::Mirror()
{
    Mirror(mpRoot);
}


/* print */
void ExpTree::Print()
{
#ifdef VERBOSE
    PrintLevelOrder();
    printf("\n");
#endif
}


/* evaluate the tree
 */
void
ExpTree::EvaluateTree()
{
    if (mpRoot)
        EvaluateRek(mpRoot);
}


/* get an infix expression
 *
 * @param pointer to an allocated string where the expression
 *        is placed
 */
void
ExpTree::GetInfixExp(char *pString)
{
    if (mpRoot)
    {
        int r_cur_str_idx = 0;
        CreateInfixExp(mpRoot, r_cur_str_idx, pString);

        pString[r_cur_str_idx] = '\0';
    }
}
/*============================= ACESS      =================================*/
/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////

/* check whether a char is an opearand
 */
bool ExpTree::CharIsOperand(char c)
{
    return ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z'));
}


/* check whether a char is an opeartor
 */
bool ExpTree::CharIsOperator(char c)
{
    return (c == '+' ||
            c == '*' ||
            c == '-' ||
            c == '/');
}


/* check whether a char is a digit
 */
bool ExpTree::CharIsDigit(char c)
{
    return (c >= '0' && c <= '9');
}


/* this method mirrors a tree on the vertical axis
 *
 * @param TreeNode pointer for recursion
 */
void ExpTree::Mirror(TreeNode* pWalker)
{
    if (pWalker != NULL)
    {
        TreeNode* p_temp = pWalker->pLeft;
        pWalker->pLeft = pWalker->pRight;
        pWalker->pRight = p_temp;

        Mirror(pWalker->pLeft);
        Mirror(pWalker->pRight);
    }
    
    return;
}


/* Exercise 2: this function evaluates a (sub-)tree recursive
 *
 * Here you find the recursive function for evaluating a expression
 * tree. Algorithm is trivial and explained in the function body.
 *
 * @param the sub tree for recursion
 *
 * @return sub tree
 */
TreeNode*
ExpTree::EvaluateRek(TreeNode *pTreePart)
{
    /* check leaf status to cancel the recursion */
    if (!pTreePart->pLeft && !pTreePart->pRight)
        return pTreePart;
    else
    {
        TreeNode* p_operand_1 = EvaluateRek(pTreePart->pLeft);
        TreeNode* p_operand_2 = EvaluateRek(pTreePart->pRight);
        
        /* calculate the if we have two digits in the left and right
         * subtrees */
        if (p_operand_1->IsDigit && p_operand_2->IsDigit)
        {
            int cur_res = 0;

            if (pTreePart->Char == '+')
                cur_res = p_operand_1->Digit + p_operand_2->Digit;
            else if (pTreePart->Char == '-')
                cur_res = p_operand_1->Digit - p_operand_2->Digit;
            else if (pTreePart->Char == '*')
                cur_res = p_operand_1->Digit * p_operand_2->Digit;
            else if (pTreePart->Char == '/')
                cur_res = p_operand_1->Digit / p_operand_2->Digit;
            else
                return pTreePart;

            /* Hint 2: If we have a negative result, we do not simplify anything */
            if (cur_res < 0)
                return pTreePart;

            pTreePart->Digit = cur_res;

            /* delete the subtrees */
            DeleteRek(pTreePart->pLeft);
            DeleteRek(pTreePart->pRight);

            pTreePart->pLeft = NULL;
            pTreePart->pRight = NULL;
            
            /* set new pTreePart status */
            pTreePart->IsDigit = true;
            pTreePart->IsOperator = false;

            return pTreePart;
        }
        
        /* special case where the op is / or - and the both childs has the same
         * variable name e.g. b/b */
        if (!pTreePart->pLeft->IsOperator && !pTreePart->pRight->IsOperator &&
            pTreePart->pLeft->Char == pTreePart->pRight->Char)
        {
            if (pTreePart->Char == '-')
                pTreePart->Digit = 0;
            else if (pTreePart->Char == '/')
                pTreePart->Digit = 1;
            else
                return pTreePart;
           
            pTreePart->IsDigit = true;
            pTreePart->IsOperator = false;

            /* delete subtrees */
            DeleteRek(pTreePart->pLeft);
            DeleteRek(pTreePart->pRight);

            pTreePart->pLeft = NULL;
            pTreePart->pRight = NULL;

            return pTreePart;
        }

        /* special case where we have one variable and zero as operands */

        /* 0 + a, 0 / a, 0 * a */
        if (pTreePart->pLeft->IsDigit &&
            pTreePart->pLeft->Digit == 0 &&
            !pTreePart->pRight->IsOperator)
        {
            if (pTreePart->Char == '+')
                pTreePart->Char = pTreePart->pRight->Char;
            else if (pTreePart->Char == '/')
            {
                pTreePart->Digit = 0;
                pTreePart->IsDigit = true;
            }
            else if (pTreePart->Char == '*')
            {
                pTreePart->Digit = 0;
                pTreePart->IsDigit = true;
            }
            /* 0 - a is excluded */
            else
                return pTreePart;

            /* delete subtrees */
            DeleteRek(pTreePart->pLeft);
            DeleteRek(pTreePart->pRight);

            pTreePart->pLeft = NULL;
            pTreePart->pRight = NULL;

            pTreePart->IsOperator = false;

            return pTreePart;
        }

        /* a + 0, a - 0, a * 0 */
        if (pTreePart->pRight->IsDigit &&
            pTreePart->pRight->Digit == 0 &&
            !pTreePart->pLeft->IsOperator)
        {
            if (pTreePart->Char == '+' || pTreePart->Char == '-')
                pTreePart->Char = pTreePart->pLeft->Char;
            else if (pTreePart->Char == '*')
            {
                pTreePart->Digit = 0;
                pTreePart->IsDigit = true;
            }
            /* a / 0 is excluded */
            else
                return pTreePart;

            /* delete subtrees */
            DeleteRek(pTreePart->pLeft);
            DeleteRek(pTreePart->pRight);

            pTreePart->pLeft = NULL;
            pTreePart->pRight = NULL;

            pTreePart->IsOperator = false;

            return pTreePart;
        }
    }
    /* if we are here no simplification is possible */ 
    return pTreePart;
}


/* Exercise 3: create an infix expression
 *
 * Because of the nature of an expression tree, we can parse the tree
 * in inorder way to get an infix expression. It is also possible
 * to parse an expression tree in postorder to get the postfix expression
 * and in preorder to get the prefix expression.
 *
 * @param tree node for recusion
 * @param reference for index of the string 
 * @param the string where the expression will be written
 */
void
ExpTree::CreateInfixExp(TreeNode *pTreePart, int &rCurStrIdx, char *pString)
{
    /* check for leaf */
    if (!pTreePart->pLeft && !pTreePart->pRight)
    {
        if (pTreePart->IsDigit)
            pString[rCurStrIdx] = (char)(pTreePart->Digit + 48);
        else
            pString[rCurStrIdx] = pTreePart->Char;

        rCurStrIdx++;
    }
    else
    {
        /* here we always have a opeartor */
        pString[rCurStrIdx] = '(';
        rCurStrIdx++;
        CreateInfixExp(pTreePart->pLeft, rCurStrIdx, pString);

        pString[rCurStrIdx] = pTreePart->Char;
        rCurStrIdx++;

        CreateInfixExp(pTreePart->pRight, rCurStrIdx, pString);

        pString[rCurStrIdx] = ')';
        rCurStrIdx++;
    }
    return;
}


/* rec function for printing */
void ExpTree::PrintRek(TreeNode* pWalker)
{
#ifdef VERBOSE
    if (pWalker != NULL)
    {
        printf("%d |", pWalker->Digit);
        PrintRek(pWalker->pLeft);
        PrintRek(pWalker->pRight);
    }
#endif
}


/* print tree in level order */
void ExpTree::PrintLevelOrder()
{
#ifdef VERBOSE
    if (mpRoot == NULL)
        return;

    Queue q;
    q.Enqueue(mpRoot);

    int nodes_current_level = 1;
    int nodes_next_level = 0;
    
    while (q.IsEmpty() != true)
    {
        TreeNode* pTemp = q.Dequeue();
        
        printf("| %d ", pTemp->Digit);

        nodes_current_level--;

        if (pTemp->pLeft != NULL)
        {
            q.Enqueue(pTemp->pLeft);
            nodes_next_level++;
        }

        if (pTemp->pRight != NULL)
        {
            q.Enqueue(pTemp->pRight);
            nodes_next_level++;
        }

        if (nodes_current_level == 0)
        {
            printf("|\n");
            nodes_current_level = nodes_next_level;
            nodes_next_level = 0;
        }
    }
#endif
}
