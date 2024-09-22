#include <iostream>
#include <string>
#include <windows.h>
#include <locale>

char * a = setlocale(LC_ALL, "zh_CN.UTF-8");

typedef void (*cmdParseFunction)(LPCTSTR s);
typedef BOOL (*debugPrtf)(LPCWSTR s);
typedef BOOL (*debugSetCmdFunc)(cmdParseFunction func);
typedef void (*UiInitalFunc)();

// void cmdParse(LPCTSTR s)
// {
//     dbgPrtf(L"cmdParse - start");
//     LPCWSTR temp = (LPCWSTR)s;
//     LPCWSTR test = LPCWSTR(L"test");
//     if (wcscmp(temp, test) == 0)
//     {
//         dbgPrtf(L"test - debugconsole command");
//     }
// }

int main()
{
    //dbgPrtf(L"DebugConsoleTest - start");
    //dbgSetCmdFunc(cmdParse);
    //dbgPrtf(L"DebugConsoleTest - end");
    HINSTANCE hDll = LoadLibrary(LPCTSTR("libDebugConsoleZero.dll"));
    auto UiInital = (UiInitalFunc)GetProcAddress(hDll, "UiInital");
    //auto dbgSetCmdFunc = (debugSetCmdFunc)GetProcAddress(hDll, "setCmdParseFunc");
    UiInital();
    MessageBox(NULL, (LPCSTR)L"Press OK to continue...", (LPCSTR)L"Pause", MB_OK | MB_ICONINFORMATION);
}
