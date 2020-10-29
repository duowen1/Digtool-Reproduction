#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
using namespace std;

bool GetSystemThread() {
	HANDLE ThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (ThreadSnap == INVALID_HANDLE_VALUE) {
		cout << "[GetSystemThread] Get Thread Snap fail." << endl;
		return false;
	}

	THREADENTRY32 ThreadInfo = { 0 };
	ThreadInfo.dwSize = sizeof(ThreadInfo);

	bool Res = Thread32First(ThreadSnap, &ThreadInfo);


	cout << "PID TID" << endl;

	while (Res) {
		cout << ThreadInfo.th32OwnerProcessID << " " << ThreadInfo.th32ThreadID << endl;
		Res = Thread32Next(ThreadSnap, &ThreadInfo);
	}
	CloseHandle(ThreadSnap);

	return true;
}