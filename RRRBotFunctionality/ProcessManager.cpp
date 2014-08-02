#include <vector>
#include <utility>
#include <fstream>
#include "ProcessManager.h"
#include <tlhelp32.h>
#include <psapi.h>

CProcessManagerException::CProcessManagerException()
	:	CProcessManagerException(GetLastError())
{ }

CProcessManagerException::CProcessManagerException(DWORD errorCode)
	: m_dwErrorCode(errorCode)
{
	std::vector<char> message(256, '\0');

	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM,                 // It´s a system error
		NULL,                                      // No string to be formatted needed
		m_dwErrorCode,                               // Hey Windows: Please explain this error!
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  // Do it in the standard language
		&message[0],              // Put the message here
		message.size() - 1,                     // Number of bytes to store the message
		NULL
	);
	m_strMessage.assign(message.begin(), message.end());
}

CProcessManagerException::CProcessManagerException(std::string message)
	: m_strMessage(message)
{ }

const char* CProcessManagerException::what() const
{
	return m_strMessage.c_str();
}

CProcessManager::CProcessManager()
	:	m_dwPid(NULL), m_hProcess(NULL), m_hWindowHandle(NULL)
{ }

CProcessManager::~CProcessManager()
{
	if (NULL != m_hProcess)
	{
		CloseHandle(m_hProcess);
	}
}

bool CProcessManager::isConfigured() const
{
	return
		(NULL != m_dwPid) &&
		(NULL != m_hWindowHandle) &&
		(NULL != m_hProcess);
}

void CProcessManager::configureByWindowTitle(std::string windowTitle)
{
	setPrivilages();
	setUpWindowHandleByTitle(windowTitle);
	setUpProcessHandleByTitle(windowTitle);
}

void CProcessManager::configureByProcessName(std::string processName)
{
	setPrivilages();
	setUpProcessHandleByProcessName(processName);
	setUpWindowHandleByProcessName(processName);	
}

void CProcessManager::setUpWindowHandleByProcessName(std::string processName)
{
	struct EnumData {
		DWORD dwProcessId;
		HWND hWnd;
	};

	EnumData ed = { m_dwPid };

	auto enumProcFunc = 
		[](HWND hWnd, LPARAM lParam) -> BOOL
		{
			EnumData& ed = *reinterpret_cast<EnumData*>(lParam);
			DWORD dwProcessId = 0x0;
			GetWindowThreadProcessId(hWnd, &dwProcessId);

			if (ed.dwProcessId == dwProcessId) {
				ed.hWnd = hWnd;
				SetLastError(ERROR_SUCCESS);
				return FALSE;
			}
			return TRUE;
		};

	EnumWindows(enumProcFunc, (LPARAM)&ed);
	DWORD dwErrCode = GetLastError();

	if (dwErrCode != ERROR_SUCCESS)
	{
		throw CProcessManagerException(dwErrCode);
	}
	m_hWindowHandle = ed.hWnd;
}

void CProcessManager::setUpWindowHandleByTitle(std::string windowTitle)
{
	HWND windowHandle = FindWindow(NULL, windowTitle.c_str());
	if (NULL == windowHandle)
	{
		throw CProcessManagerException();
	}
	m_hWindowHandle = windowHandle;
}

void CProcessManager::setUpProcessHandleByTitle(std::string windowTitle)
{
	DWORD dwProcessId = 0;
	DWORD dwThreadId = GetWindowThreadProcessId(m_hWindowHandle, &dwProcessId);
	if (NULL == dwThreadId)
	{
		throw CProcessManagerException();
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (NULL == hProcess)
	{
		throw CProcessManagerException();
	}
	m_dwPid = dwProcessId;
	m_hProcess = hProcess;
}

void CProcessManager::setUpProcessHandleByProcessName(std::string processName)
{
	setPrivilages();
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (NULL == snapshot)
	{
		throw CProcessManagerException();
	}

	if (TRUE == Process32First(snapshot, &entry))
	{
		while (TRUE == Process32Next(snapshot, &entry))
		{
			if (processName == std::string(entry.szExeFile))
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				if (NULL == hProcess)
				{
					throw CProcessManagerException();
				}
				m_hProcess = hProcess;
				m_dwPid = entry.th32ProcessID;
			}			
		}
	}

	CloseHandle(snapshot);
}

void CProcessManager::setPrivilages()
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkp;

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = luid;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(hToken, false, &tkp, sizeof(tkp), NULL, NULL);

	CloseHandle(hToken);
}

std::vector<std::pair<std::string, HMODULE> > CProcessManager::getModules()
{
	if (!isConfigured())
	{
		throw CProcessManagerException("ProcessManager is not configured, configure first!");
	}

	HMODULE hMods[1024];
	DWORD cbNeeded;
	unsigned int i;
	std::vector<std::pair<std::string, HMODULE> > result;
	
	BOOL operationResult = EnumProcessModules(m_hProcess, hMods, sizeof(hMods), &cbNeeded);
	if (FALSE == operationResult)
	{
		throw CProcessManagerException();
	}

	for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
	{
		TCHAR szModName[MAX_PATH];

		operationResult = GetModuleFileNameEx(m_hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR));
		if (FALSE == operationResult)
		{
			throw CProcessManagerException();
		}
		std::string moduleName = szModName;
		moduleName.assign(moduleName.begin() + moduleName.rfind("\\") + 1, moduleName.end());
		result.push_back(std::make_pair(moduleName, hMods[i]));
	}
	return result;
}

HMODULE CProcessManager::getModuleAddress(std::string moduleName)
{
	auto modules = getModules();
	
	for (auto& module : modules)
	{
		if (module.first == moduleName)
		{
			return module.second;
		}
	}
	return NULL;	
}

bool CProcessManager::isValidAddress(DWORD address, size_t nBytes)
{
	MEMORY_BASIC_INFORMATION mbi;
	
	BOOL operationResult = VirtualQueryEx(m_hProcess, (void*)address, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
	if (FALSE == operationResult)
	{
		throw CProcessManagerException();
	}

	if (mbi.State != MEM_COMMIT)
	{
		return false;
	}

	if (mbi.Protect == PAGE_NOACCESS || mbi.Protect == PAGE_EXECUTE)
	{
		return false;
	}

	size_t blockOffset = (size_t)((char *)address - (char *)mbi.AllocationBase);
	size_t blockBytesPostPtr = mbi.RegionSize - blockOffset;

	if (blockBytesPostPtr < nBytes)
	{
		return isValidAddress(address + blockBytesPostPtr, nBytes - blockBytesPostPtr);
	}

	return true;
}

HWND CProcessManager::getWindowHandle() const
{
	if (!isConfigured())
	{
		throw CProcessManagerException("ProcessManager is not configured, configure first!");
	}
	return m_hWindowHandle;
}

DWORD CProcessManager::getProcessId() const
{
	if (!isConfigured())
	{
		throw CProcessManagerException("ProcessManager is not configured, configure first!");
	}
	return m_dwPid;
}

HANDLE CProcessManager::getProcessHandle() const
{
	if (!isConfigured())
	{
		throw CProcessManagerException("ProcessManager is not configured, configure first!");
	}
	return m_hProcess;
}