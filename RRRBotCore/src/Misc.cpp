#include <Shlobj.h>
#include "Misc.h"

BOOL CALLBACK EnumProc( HWND hWnd, LPARAM lParam ) {
    // Retrieve storage location for communication data
    GetProcessWindowHandleData& ed = *(GetProcessWindowHandleData*)lParam;
    DWORD dwProcessId = 0x0;
    // Query process ID for hWnd
    GetWindowThreadProcessId( hWnd, &dwProcessId );

    if ( ed.dwProcessId == dwProcessId ) {
        ed.hWnd = hWnd;
        // Report success
        SetLastError( ERROR_SUCCESS );
        // Stop enumeration
        return FALSE;
    }
    // Continue enumeration
    return TRUE;
}

HWND FindWindowFromProcessId( DWORD dwProcessId ) {
    GetProcessWindowHandleData ed = { dwProcessId };
    if ( !EnumWindows( EnumProc, (LPARAM)&ed ) &&
         ( GetLastError() == ERROR_SUCCESS ) ) {
        return ed.hWnd;
    }
    return NULL;
}

std::string GetAppDataFolderPath()
{
    TCHAR szPath[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath)))
    {
        return szPath;
    }
    return "";
}

bool IsMemoryReadable(void *ptr, size_t byteCount)
{
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery(ptr, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) == 0)
    {
        return false;
    }

    if (mbi.State != MEM_COMMIT)
    {
        return false;
    }

    if (mbi.Protect == PAGE_NOACCESS || mbi.Protect == PAGE_EXECUTE)
    {
        return false;
    }

    size_t blockOffset = (size_t)((char *)ptr - (char *)mbi.AllocationBase);
    size_t blockBytesPostPtr = mbi.RegionSize - blockOffset;

    if (blockBytesPostPtr < byteCount)
    {
        return IsMemoryReadable((char *)ptr + blockBytesPostPtr, byteCount - blockBytesPostPtr);
    }

  return true;
}
