#include "stdafx.h"
#include <windows.h>
#include <iostream>

#include "hack.h"
#include "injector.h"

int main()
{
		// Open Warcraft 3, and get the handle of the process
        HWND hwar3 = FindWindow(NULL, L"Warcraft III");
		if (!hwar3)
		{
			std::cout << "Warcraft 3 is not running..." << std::endl;
			return 1;
		}

		// Get Token of the user's process
        HANDLE hcurrent = GetCurrentProcess();
        HANDLE hToken;

        BOOL process = OpenProcessToken(hcurrent, 40, &hToken);
        LUID luid;

		// Check if the user got debug Privilege
        process = LookupPrivilegeValue(NULL, L"SeDebugPrivilege", &luid);
        TOKEN_PRIVILEGES NewState, PreviousState;
        DWORD ReturnLength;
        NewState.PrivilegeCount = 1;
        NewState.Privileges[0].Luid = luid;
        NewState.Privileges[0].Attributes = 2;
        process = AdjustTokenPrivileges(hToken, FALSE, &NewState, 28, &PreviousState, &ReturnLength);
       
        DWORD PID, TID, JUMP;
        TID = GetWindowThreadProcessId(hwar3, &PID);
        HANDLE hopen = OpenProcess(
                PROCESS_ALL_ACCESS|PROCESS_TERMINATE|PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE, FALSE, PID
        );

        //0x66 0xB9 0x0F 0x00
        // Replace 'mov cx, 000F
       
        JUMP = 0x000FB966;
        process = WriteProcessMemory(hopen, (LPVOID)0x6F3A1563, &JUMP, 4, 0);
       
        process = CloseHandle(hopen);
       
        return 0;
}