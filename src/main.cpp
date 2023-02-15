#include "globals.hpp"
#include <Windows.h>


t_Login Login; 
t_Logout Logout; 
t_Status GetStatus; 
t_Username GetUsername; 
t_Modules GetModules; 
t_Inject Inject;

#ifdef _WINDLL


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);
        CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)UI::Render, nullptr, NULL, nullptr);
        return TRUE;
    }

    return TRUE;
}

#else

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
    // load the loader binary file
    auto shadow = LoadLibraryA("loader.dll");
    // If the module is not found then alert the user and close
    if (!shadow) {
        MessageBoxA(0, "Failed to load loader binary.", "Shadow Client - Error", MB_OK);
        exit(1);
    }
    // Update module info
    Login = (t_Login)GetProcAddress(shadow, "Login");
    Logout = (t_Logout)GetProcAddress(shadow, "Logout");
    GetStatus = (t_Status)GetProcAddress(shadow, "GetStatus");
    GetUsername = (t_Username)GetProcAddress(shadow, "GetUsername");
    GetModules = (t_Modules)GetProcAddress(shadow, "GetModuleList");
    Inject = (t_Inject)GetProcAddress(shadow, "Inject");

    // render the window
    UI::Render();

    return 0;
}

#endif