#include "DebugConsoleDll.h"

HINSTANCE DebugConsoleDll::hDll = NULL;
UiInitalFunc DebugConsoleDll::UiInital = nullptr;
dbgDebugFunc DebugConsoleDll::dbgDebug = nullptr;
dbgInfoFunc DebugConsoleDll::dbgInfo = nullptr;
dbgWarningFunc DebugConsoleDll::dbgWarning = nullptr;
dbgErrorFunc DebugConsoleDll::dbgError = nullptr;
dbgFatalFunc DebugConsoleDll::dbgFatal = nullptr;
setCustomCmdEventFunc DebugConsoleDll::setCustomCmdEvent = nullptr;

DebugConsoleDll::DebugConsoleDll()
{

}

void DebugConsoleDll::Initalize()
{
    hDll = LoadLibrary(L".\\libDebugConsoleZero.dll");
    if (hDll == NULL)
    {
        return;
    }
    UiInital = (UiInitalFunc)GetProcAddress(hDll, "UiInital");
    dbgDebug = (dbgDebugFunc)GetProcAddress(hDll, "dbgDebug");
    dbgInfo = (dbgInfoFunc)GetProcAddress(hDll, "dbgInfo");
    dbgWarning = (dbgWarningFunc)GetProcAddress(hDll, "dbgWarning");
    dbgError = (dbgErrorFunc)GetProcAddress(hDll, "dbgError");
    dbgFatal = (dbgFatalFunc)GetProcAddress(hDll, "dbgFatal");
    setCustomCmdEvent = (setCustomCmdEventFunc)GetProcAddress(hDll, "setCustomCmdEvent");
    UiInital();
}
