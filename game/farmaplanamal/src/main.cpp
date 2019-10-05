#include <iostream>
#include "universal/license.h"
#include "game.h"

#define P_VERSION "0";

int main()
{
    perennial::information::License();
    return perennial::GameLoop(); //So we get -1 if we fuck up.

}