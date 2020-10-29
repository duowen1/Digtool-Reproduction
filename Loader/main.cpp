#include <iostream>
#include <windows.h>
using namespace std;

void PrintBanner();
extern bool SystemCheck();
extern bool HardwareCheck();
extern bool StartDriver();
extern HANDLE InitCommunicate();
extern bool GetSystemThread();

int main() {
	//Êä³öBannner
	PrintBanner();

	bool Res = true;

	cout << "[Main] Checking Your System..." << endl;
	Res = SystemCheck();
	if (!Res) {
		cout << "[Main] Not Support System" << endl;
		return 0;
	}

	cout << "[Main] Checking Your Hardware" << endl;
	Res = HardwareCheck();
	if (!Res) {
		cout << "[Main] Not Support Hardware" << endl;
		return 0;
	}

	cout << "[Main] It is going to load the Hypervisor and it takes time." << endl;
	Res = StartDriver();
	if (!Res) {
		cout << "[Main] Start Driver Fail" << endl;
		system("pause");
		return 0;
	}

	bool GetSystemThread();

	HANDLE Handle = NULL;
	//Handle = InitCommunicate();
	if (Handle == INVALID_HANDLE_VALUE) {
		DWORD ErrorCode = GetLastError();
		cout << "[Main] CreatFile faild : " << ErrorCode << endl;
		return 0;
	}

	//Res = StartFuzzer();
	if (!Res) {

		return 0;
	}

	system("pause");
	return 0;
}

void PrintBanner() {
	
	return;
}