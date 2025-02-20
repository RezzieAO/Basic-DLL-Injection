// injection.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <Windows.h>


using namespace std;


int main(int argc, char* argv[])
{
	
	// path to our dll
	LPCSTR DllPath = "C:\\dllmain.dll";

	// Open a handle to target process - by entering its PID as parameter
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, atoi(argv[1]));

	if (!hProcess)
	{
		cout << "cant open process" << endl;
		Sleep(3000);
		return 1;
	}

	// Allocate memory for the dllpath in the target process
	// length of the path string + null terminator
	LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath) + 1,
		MEM_COMMIT, PAGE_READWRITE);


	// Write the path to the address of the memory we just allocated
	// in the target process
	WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath, strlen(DllPath) + 1, 0);


	// Create a Remote Thread in the target process which
	// calls LoadLibraryA as our dllpath as an argument -> program loads our dll
	HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), pDllPath, 0, 0);


	// Wait for the execution of our loader thread to finish
	WaitForSingleObject(hLoadThread, INFINITE);


	cout << "Dll path allocated at: " << hex << pDllPath << endl;
	


	// Free the memory allocated for our dll path
	VirtualFreeEx(hProcess, pDllPath, strlen(DllPath) + 1, MEM_RELEASE);


	system("pause");
	return 0;
}