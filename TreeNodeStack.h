
/* TreeNodeStack.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-06-21.
 * @Editor:      Vim
 */

#ifndef TREENODESTACK_H
#define TREENODESTACK_H

#ifndef NULL
#define NULL 0
#endif

#include "ExpTree.h"

struct TreeNode;

class TreeNodeStack
{
    typedef TreeNode* ElemType;

    struct StackNode
    {
        ElemType      mData;
        StackNode*    mpPrev;

        StackNode()
        :   mData(0),
            mpPrev(NULL)
        {
        }
    };

    StackNode* mpHead;

    public:

    TreeNodeStack();
    ~TreeNodeStack();

    bool        IsEmpty();
    void        Push(ElemType pushedValue);
    bool        Pop(ElemType* pPopedValue);
};
#endif
