
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

/*============================= ACESS      =================================*/
/*============================= INQUIRY    =================================*/
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
