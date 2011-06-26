
/* main.cpp<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-06-21.
 * @Editor:      Vim
 */

#include <stdio.h>

#include "ChStack.h"
#include "ExpTree.h"
#include "Helpers.h"

int main(int argc, char* argv[])
{

    /** handle arguments
     *
     * We only treat the first argument
     */

    /* cancel if no expression is given */
    if (argc <= 1)
    {
        printf("No expression given. Exiting ...\n");
        return 1;
    }
    
    /* get the expression */
    char* p_expression = argv[1];

    if (Helpers::StringLen(p_expression) == 0)
    {
        printf("No expression given. Exiting ...\n");
        return 1;
    }


    /** Tree handling
     */

    ExpTree tree;
    
    tree.InsertExp(p_expression);


    /** Tree evaluation
     */

    /* allocate string, remember the terminator */
    char* p_result = new char[Helpers::StringLen(p_expression) + 1];

    tree.EvaluateTree();
    tree.GetInfixExp(p_result);

    printf("Infix Expression: %s\n", p_result);
    
    delete[] p_result;

    return 0;
}
