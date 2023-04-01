#include <stdio.h>
#include <string.h>
#include "logging.h"

/*main code*/

int main(int argc, char *argv[])
{
    LOGERROR("Here is error 1 with...");
    LOGERROR("Here is error 2 with...");
    nConfigLogLevel = 2;
    LOGDEBUG("Here is bug debug 1");
    LOGDEBUG("Here is bug debug 2");
    LOGINFO("Info Info Info");
    LOGINFO("Info Info Info");
    LOGINFO("Info Info Info");
    return 0;
}
