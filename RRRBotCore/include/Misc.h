#ifndef MISC_H
#define MISC_H

#include <string>
#include "stdafx.h"

struct GetProcessWindowHandleData {
    DWORD dwProcessId;
    HWND hWnd;
};

BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam);
HWND FindWindowFromProcessId(DWORD dwProcessId);
std::string GetAppDataFolderPath();
bool IsMemoryReadable(void* ptr, size_t byteCount);

#endif // MISC_H
