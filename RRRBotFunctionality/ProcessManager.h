#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <string>
#include <stdexcept>
#include <vector>
#include "stdafx.h"

class CProcessManagerException : std::exception
{
public:
	CProcessManagerException();
	CProcessManagerException(DWORD errorCode);
	CProcessManagerException(std::string message);

	const char* what() const;
private:
	DWORD m_dwErrorCode;
	std::string m_strMessage;
};

class CProcessManager
{
public:
	CProcessManager();
	~CProcessManager();

	bool isConfigured() const;
	void configureByWindowTitle(std::string windowTitle);
	void configureByProcessName(std::string processName);

	std::vector<std::pair<std::string, HMODULE> > getModules();
	HMODULE getModuleAddress(std::string moduleName);
	HWND getWindowHandle() const;
	DWORD getProcessId() const;
	HANDLE getProcessHandle() const;

	bool isValidAddress(DWORD address, size_t nBytes);

	template <typename T>
	void writeMemory(DWORD address, T value)
	{
		BOOL operationResult = WriteProcessMemory(m_hProcess, reinterpret_cast<LPVOID>(address), &value, sizeof(T), NULL);
		if (FALSE == operationResult)
		{
			throw CProcessManagerException();
		}
	}

	template <typename T>
	void writeMemory(DWORD address, T* values, size_t nBytes)
	{
		size_t nBytesWritten;
		BOOL operationResult = WriteProcessMemory(m_hProcess, address, values, nBytes, NULL);
		if (FALSE == operationResult)
		{
			throw CProcessManagerException();
		}
	}
	
	template <typename T>
	T readMemory(DWORD address)
	{
		T result;
		BOOL operationResult = ReadProcessMemory(m_hProcess, reinterpret_cast<LPCVOID>(address), &result, sizeof(T), NULL);
		if (FALSE == operationResult)
		{
			throw CProcessManagerException();
		}
		return result;
	}

	template <typename T>
	std::vector<T> readMemory(DWORD address, size_t nBytes)
	{
		std::vector<T> result(nBytes);

		BOOL operationResult = ReadProcessMemory(m_hProcess, address, &result[0], nBytes, NULL);
		if (FALSE == operationResult)
		{
			throw CProcessManagerException();
		}
		return result;
	}

private:
	HWND m_hWindowHandle;
	DWORD m_dwPid;
	HANDLE m_hProcess;
	
	void setUpWindowHandleByTitle(std::string windowTitle);
	void setUpWindowHandleByProcessName(std::string processName);
	void setUpProcessHandleByTitle(std::string windowTitle);
	void setUpProcessHandleByProcessName(std::string processName);
	void setPrivilages();
};

#endif