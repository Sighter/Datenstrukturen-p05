
/* ChStack.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-06-21.
 * @Editor:      Vim
 */

#ifndef CHSTACK_H
#define CHSTACK_H

#ifndef NULL
#define NULL 0
#endif

typedef char ElemType;

struct ChStackNode
{
    ElemType        mData;
    ChStackNode*    mpPrev;

    ChStackNode()
    :   mData(0),
        mpPrev(NULL)
    {
    }
};

class ChStack
{
    ChStackNode* mpHead;

    public:

    ChStack();
    ~ChStack();
    
    bool        IsEmpty();
    void        Push(ElemType pushedValue);
    bool        Pop(ElemType& rPopedValue);
};
#endif
