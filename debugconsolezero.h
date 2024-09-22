#ifndef DEBUGCONSOLEZERO_H
#define DEBUGCONSOLEZERO_H

#include "DebugConsoleZero_global.h"
#include "form.h"

extern Form ui;

extern "C" __declspec(dllexport) void UiInital();
extern "C" __declspec(dllexport) void dbgDebug(std::string s);
extern "C" __declspec(dllexport) void dbgInfo(std::string s);
extern "C" __declspec(dllexport) void dbgWarning(std::string s);
extern "C" __declspec(dllexport) void dbgError(std::string s);
extern "C" __declspec(dllexport) void dbgFatal(std::string s);
extern "C" __declspec(dllexport) void setCustomCmdEvent(void (*func)(std::string));

#endif // DEBUGCONSOLEZERO_H
