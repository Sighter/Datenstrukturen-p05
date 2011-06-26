
/* TreeNodeStack.cc
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-06-21.
 * @Editor:      Vim
 */

#include "TreeNodeStack.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/* stack constructor
 */
TreeNodeStack::TreeNodeStack()
:   mpHead(NULL)
{
}


/* stack destructor
 */
TreeNodeStack::~TreeNodeStack()
{
    StackNode* p_walker = mpHead;
    
    while (p_walker)
    {
        StackNode* p_del = p_walker;
        p_walker = p_walker->mpPrev;
        delete p_del;
    }
}

/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/

/* push a value on the stack
 */
void TreeNodeStack::Push(ElemType pushedValue)
{
    StackNode* p_new_item = new StackNode;
    
    p_new_item->mData = pushedValue;
    p_new_item->mpPrev = mpHead;

    mpHead = p_new_item;
}


/* get an element from the stack by reference
 *
 * @param reference to the variable where popped value is been placed
 *
 * @return false if stack is empty otherwise true
 */
bool TreeNodeStack::Pop(ElemType* pPopedValue)
{
    if (IsEmpty())
        return false;
    
    *pPopedValue = mpHead->mData;
    
    StackNode* p_del = mpHead;
    mpHead = mpHead->mpPrev;

    delete p_del;

    return true;
}

/*============================= ACESS      =================================*/
/*============================= INQUIRY    =================================*/

/* check for stack emptyness
 */
bool TreeNodeStack::IsEmpty()
{
    if (!mpHead)
        return true;
    else
        return false;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
