
/* helpers.h
 * @Author:      The Sighter (sighter@resource-dnb.de)
 * @License:     GPL
 * @Created:     2011-06-21.
 * @Editor:      Vim
 */

#ifndef HELPERS_H
#define HELPERS_H

#ifndef NULL
#define NULL 0
#endif

#include "ChStack.h"

/** class with some helper functions
 */
class Helpers
{
public:
    static int  StringLen(char* pString);
    static bool InfixToPostfix(char* pInfix, char* pPostfix);
};




#endif
