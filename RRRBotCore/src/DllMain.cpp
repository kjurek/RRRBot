#include "stdafx.h"
#include "RRRBot.h"

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
            RRRBot::CRRRBot::getInstance().run();
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
