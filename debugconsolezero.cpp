#include "debugconsolezero.h"

Form ui;

extern "C" __declspec(dllexport) void UiInital()
{
    ui.show();
}

extern "C" __declspec(dllexport) void dbgDebug(std::string s)
{
    ui.dbgPrtf(debug, s);
}

extern "C" __declspec(dllexport) void dbgInfo(std::string s)
{
    ui.dbgPrtf(info, s);
}

extern "C" __declspec(dllexport) void dbgWarning(std::string s)
{
    ui.dbgPrtf(warning, s);
}

extern "C" __declspec(dllexport) void dbgError(std::string s)
{
    ui.dbgPrtf(error, s);
}

extern "C" __declspec(dllexport) void dbgFatal(std::string s)
{
    ui.dbgPrtf(fatal, s);
}

extern "C" __declspec(dllexport) void setCustomCmdEvent(void (*func)(std::string))
{
    ui.customCmdEventFunc = func;
}
