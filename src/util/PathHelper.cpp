#include "util/PathHelper.h"

using namespace std;

PathHelper::PathHelper()
{
    int ret;
    pid_t pid; 
    char pathbuf[PROC_PIDPATHINFO_MAXSIZE];

    pid = getpid();
    ret = proc_pidpath (pid, pathbuf, sizeof(pathbuf));
    if ( ret <= 0 ) {
        throw "Unable to ascertain application path";
    } else {
        string fullPath = string(pathbuf);
        applicationPath = fullPath.substr(0, fullPath.find_last_of("/"));
        applicationName = fullPath.substr(fullPath.find_last_of("/") + 1, fullPath.length());
    }
}

PathHelper::~PathHelper()
{

}

const string& PathHelper::getApplicationPath()
{
    return applicationPath;
}

const string& PathHelper::getApplicationName()
{
    return applicationName;
}