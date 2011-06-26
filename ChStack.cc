
/* ChStack.cc
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-06-21.
 * @Editor:      Vim
 */

#include "ChStack.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/* stack constructor
 */
ChStack::ChStack()
:   mpHead(NULL)
{
}


/* stack destructor
 */
ChStack::~ChStack()
{
    ChStackNode* p_walker = mpHead;
    
    while (p_walker)
    {
        ChStackNode* p_del = p_walker;
        p_walker = p_walker->mpPrev;
        delete p_del;
    }
}

/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/

/* push a value on the stack
 */
void ChStack::Push(ElemType pushedValue)
{
    ChStackNode* p_new_item = new ChStackNode;
    
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
bool ChStack::Pop(ElemType& rPopedValue)
{
    if (IsEmpty())
        return false;
    
    rPopedValue = mpHead->mData;
    
    ChStackNode* p_del = mpHead;
    mpHead = mpHead->mpPrev;

    delete p_del;

    return true;
}

/*============================= ACESS      =================================*/
/*============================= INQUIRY    =================================*/

/* check for stack emptyness
 */
bool ChStack::IsEmpty()
{
    if (!mpHead)
        return true;
    else
        return false;
}

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
