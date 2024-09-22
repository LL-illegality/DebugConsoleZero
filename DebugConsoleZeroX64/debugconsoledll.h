#ifndef DEBUGCONSOLEDLL_H
#define DEBUGCONSOLEDLL_H

#include <windows.h>
#include <string>

typedef void (*UiInitalFunc)();
typedef void (*dbgDebugFunc)(std::string s);
typedef void (*dbgInfoFunc)(std::string s);
typedef void (*dbgWarningFunc)(std::string s);
typedef void (*dbgErrorFunc)(std::string s);
typedef void (*dbgFatalFunc)(std::string s);
typedef void (*setCustomCmdEventFunc)(void (*func)(std::string));

class DebugConsoleDll
{
public:
    static HINSTANCE hDll;
    static UiInitalFunc UiInital;
    static dbgDebugFunc dbgDebug;
    static dbgInfoFunc dbgInfo;
    static dbgWarningFunc dbgWarning;
    static dbgErrorFunc dbgError;
    static dbgFatalFunc dbgFatal;
    static setCustomCmdEventFunc setCustomCmdEvent;
    static void Initalize();
    DebugConsoleDll();
};

#define debug DebugConsoleDll::dbgDebug
#define info DebugConsoleDll::dbgInfo
#define warning DebugConsoleDll::dbgWarning
#define error DebugConsoleDll::dbgError
#define fatal DebugConsoleDll::dbgFatal
#define setCmdEvent DebugConsoleDll::setCustomCmdEvent

#endif // DEBUGCONSOLEDLL_H
