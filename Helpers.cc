
/* Helpers.cc<++>
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-06-21.
 * @Editor:      Vim
 */

#include "Helpers.h"


/////////////////////////////// PUBLIC ///////////////////////////////////////

/*============================= LIFECYCLE ==================================*/

/*============================= OPERATORS ==================================*/

/*============================= OPERATIONS =================================*/


/** calc lenqth of a String
 * 
 * @param a pointer to a c-string
 * 
 * @return the lenqth
 */
/*static*/ int
Helpers::StringLen(char *pString)
{
    if (pString)
    {
        int c = 0;
        char current_char = pString[0];
        
        while (current_char != '\0')
        {
            c++;
            current_char = pString[c];
        }
        return c;
    }
    return 0;
}


/** convert a infix expression to postfix format
 *
 * @param the infix expression
 * @param the pointer where the postfix expression will be written
 *
 * @return succes flag
 */
/*static*/ bool
Helpers::InfixToPostfix(char* pInfix, char* pPostfix)
{
    if (!pInfix)
        return false;

    int post_idx = 0;
    int in_idx = 0;

    ChStack converter_stack;

    while (pInfix[in_idx] != '\0')
    {
        char cur_infix_char = pInfix[in_idx];

        if ((cur_infix_char >= '0' && cur_infix_char <= '9') ||
            (cur_infix_char >= 'A' && cur_infix_char <= 'Z') ||
            (cur_infix_char >= 'a' && cur_infix_char <= 'z'))
        {
            pPostfix[post_idx] = cur_infix_char;
            post_idx++;
            in_idx++;
        }
        else if (cur_infix_char == '+' ||
                 cur_infix_char == '*' ||
                 cur_infix_char == '-' ||
                 cur_infix_char == '/')
        {
            converter_stack.Push(cur_infix_char);
            in_idx++;
        }
        else if (cur_infix_char == ')')
        {
            if (!converter_stack.Pop(pPostfix[post_idx]))
                return false;

            in_idx++;
            post_idx++;
        }
        else
        {
            in_idx++;
        }
    }
    
    pPostfix[post_idx] = '\0';

    return true;
}
/*============================= ACESS      =================================*/
/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
