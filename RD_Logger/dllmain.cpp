#include "pch.h"
#include "export.h"
#include <Windows.h>

extern HANDLE g_hMutex;
extern Logger* g_logger;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_hMutex = CreateMutex(nullptr, false, L"Global\\RD_Logger_Mutex");
        g_logger = Logger::GetInstance();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        if (g_hMutex) {
            CloseHandle(g_hMutex);
            g_hMutex = nullptr;
        }
        break;
    }
    return TRUE;
}

