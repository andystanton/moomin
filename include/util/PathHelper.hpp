#ifndef _MOOMIN_PATH_HELPER
#define _MOOMIN_PATH_HELPER

#include <string>
#include <unistd.h>
#include <limits.h>

#if defined (__APPLE__)
    #include <libproc.h>
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