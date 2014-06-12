#ifndef _MOOMIN_PATH_HELPER
#define _MOOMIN_PATH_HELPER

#include <string>
#include <unistd.h>
#include <limits.h>

#if defined (__APPLE__)
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_MAC
        #include <libproc.h>
    #endif
#endif

using std::string;

class PathHelper
{
public:
    PathHelper();
    ~PathHelper();
    
    const string& getApplicationPath();
    const string& getApplicationName();

private:
    string applicationPath;
    string applicationName;
};

#endif