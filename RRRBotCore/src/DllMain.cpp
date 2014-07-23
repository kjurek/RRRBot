#include "stdafx.h"

BOOL WINAPI DllMain(
    _In_  HINSTANCE hinstDLL,
    _In_  DWORD fdwReason,
    _In_  LPVOID lpvReserved
    )
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            MsgBox("Attach!");
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            MsgBox("Detach!");
            break;
        }
    }
    return TRUE;
}
