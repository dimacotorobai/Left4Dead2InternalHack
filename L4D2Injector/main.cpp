#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

// Function Prototypes
DWORD GetProcessId(const char*);
BOOL InjectDLL(DWORD, const char*);

int main(int argc, char* argv[])
{
    const char* szProcessName = "left4dead2.exe";
    const char* szDLLName = "Left4Dead2InternalHack.dll";

    DWORD dwProcessId = GetProcessId(szProcessName);
    if (!dwProcessId)
    {
        printf("Error - Failed to get PID of \"%s\"\n", szProcessName);
        return -1;
    }

    if (!InjectDLL(dwProcessId, szDLLName))
    {
        printf("Error - Failed to inject \"%s\"\n", szDLLName);
        return -1;
    }

    return 0;
}

DWORD GetProcessId(const char* szProcessName)
{
    DWORD dwProcessId{ 0 };
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(pe32);

        if (Process32First(hSnapshot, &pe32))
        {
            do
            {
                if (!strcmp(szProcessName, pe32.szExeFile))
                {
                    dwProcessId = pe32.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnapshot, &pe32));
        }
        CloseHandle(hSnapshot);
    }

    return dwProcessId;
}

BOOL InjectDLL(DWORD dwProcessId, const char* szDLLName)
{
    char szDLLFullPath[MAX_PATH]{ 0 };
    if (!GetFullPathName(szDLLName, MAX_PATH, szDLLFullPath, nullptr))
        return FALSE;


    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
    if (!hProcess) return FALSE;

    LPVOID pLoadLibraryA = GetProcAddress(
        GetModuleHandle("kernel32.dll"),
        "LoadLibraryA");

    LPVOID pBufferAddr = VirtualAllocEx(
        hProcess, nullptr,
        MAX_PATH, MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE);

    WriteProcessMemory(hProcess, pBufferAddr, szDLLFullPath, MAX_PATH, nullptr);

    HANDLE hThread = CreateRemoteThread(
        hProcess, nullptr, 0,
        (LPTHREAD_START_ROUTINE)pLoadLibraryA,
        pBufferAddr, 0, nullptr);
        
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    VirtualFreeEx(hProcess, pBufferAddr, 0, MEM_RELEASE);
    CloseHandle(hProcess);
    return TRUE;
}