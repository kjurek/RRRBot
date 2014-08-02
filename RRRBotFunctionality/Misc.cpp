#include <Shlobj.h>
#include "Misc.h"

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
