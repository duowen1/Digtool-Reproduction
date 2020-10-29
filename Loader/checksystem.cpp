#include <windows.h>
#include <Versionhelpers.h>
#include <iostream>
using namespace std;

bool SystemCheck();

bool SystemCheck() {
	//需要添加XML文件，暂时搁置
	if (IsWindows10OrGreater()) {
		cout << "[SystemCheck] Your OS is Windows 10 or greator." << endl;
	}
	else {
		cout << "[SystemCheck] Your system version is too low." << endl;
		return false;
	}

	SYSTEM_INFO SystemInfo;
	GetNativeSystemInfo(&SystemInfo);
	auto Architecture = SystemInfo.wProcessorArchitecture;
	if (Architecture != PROCESSOR_ARCHITECTURE_IA64 && 
		Architecture != PROCESSOR_ARCHITECTURE_AMD64) {
		cout << "[SystemCheck] Your architecture is not supported." << endl;
		return false;
	}

	return true;
}