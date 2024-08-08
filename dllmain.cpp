// dllmain.cpp : Defines the entry point for the DLL application.

#include <Windows.h>
#include <iostream>

using namespace std;

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		MessageBoxA(0, "Hello From DLLMain!", "Hello", MB_ICONINFORMATION);
		
	}

	return TRUE;
}

