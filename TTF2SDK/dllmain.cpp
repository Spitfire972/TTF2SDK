#include "stdafx.h"

DWORD WINAPI OnAttach(LPVOID lpThreadParameter)
{
    // Initialise logging - if we can't do that, we're screwed
    try
    {
        Logging::GetInstance();
    }
    catch (std::exception&)
    {
        FreeLibraryAndExitThread((HMODULE)lpThreadParameter, 0);
        return 0;
    }

    // Initialise the rest of the SDK
    try
    {
        TTF2SDK::GetInstance();
    }
    catch (std::exception& ex)
    {
        spdlog::get("logger")->info("Failed to initialise SDK: {}", ex.what());
        FreeLibraryAndExitThread((HMODULE)lpThreadParameter, 0);
        return 0;
    }

    // Wait for key press to unload DLL
    while (true)
    {
        if (GetAsyncKeyState(VK_F9))
        {
            spdlog::get("logger")->info("Unloading DLL");
            break;
        }
        Sleep(100);
    }

    FreeLibraryAndExitThread((HMODULE)lpThreadParameter, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, OnAttach, hModule, 0, NULL);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
