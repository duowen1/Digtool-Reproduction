#include <windows.h>
#include <iostream>
using namespace std;

bool StartDriver();
bool StopDriver();


bool StartDriver() {
	bool Res;
	DWORD ErrorCode;

	SC_HANDLE ServiceManagerHandle = NULL;
	ServiceManagerHandle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (ServiceManagerHandle == NULL) {
		ErrorCode = GetLastError();
		cout << "[StartDriver]OpenSCManager fail: " << ErrorCode << endl;
		return false;
	}

	SC_HANDLE ServiceHandle = NULL;
	WCHAR DriverName[] = L"MyHypervisor";
	WCHAR DriverPath[] = L"C:\\Users\\xsw\\Desktop\\Ddimon.sys";
	WCHAR DriverImagePath[256];
	GetFullPathName(DriverPath, 256, DriverImagePath, NULL);
	
	ServiceHandle = CreateService(
		ServiceManagerHandle,
		DriverName,
		DriverName,
		SERVICE_ALL_ACCESS,
		SERVICE_KERNEL_DRIVER,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_IGNORE,
		DriverImagePath,
		NULL,NULL,NULL,NULL,NULL);
	

	if (ServiceHandle == NULL) {
		ErrorCode = GetLastError();
		cout << "[StartDriver]StartService fail: " << ErrorCode << endl;
		CloseServiceHandle(ServiceManagerHandle);
		return false;
	}

	Res = StartService(ServiceHandle, NULL, NULL);
	if (!Res) {
		ErrorCode = GetLastError();
		switch (ErrorCode) {
		case ERROR_SERVICE_ALREADY_RUNNING: {
			cout << "[StartDriver]Service is already running." << endl;
			CloseServiceHandle(ServiceHandle);
			CloseServiceHandle(ServiceManagerHandle);
			break;
		}
		case ERROR_IO_PENDING: {
			cout << "[StartDriver]Service I/O PENDING." << endl;
			CloseServiceHandle(ServiceHandle);
			CloseServiceHandle(ServiceManagerHandle);
			break;
		}
		default: {
			cout << "[StartDriver]StartServiceFail: " << ErrorCode << endl;
			Res = false;
			break;
		}//default
		}//switch
	}//if

	return Res;
}


bool StopDriver() {
	bool Res;

	SC_HANDLE ServiceManagerHandle = NULL;
	WCHAR DriverName[] = L"MyHypervisor";

	ServiceManagerHandle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (ServiceManagerHandle == NULL) {
		cout << "[StopDriver] Open Service Manager fail." << endl;
		return false;
	}

	SC_HANDLE ServiceHandle = NULL;
	ServiceHandle = OpenService(ServiceManagerHandle, DriverName, SERVICE_ALL_ACCESS);
	if (ServiceHandle == NULL) {
		cout << "[StopDriver] Open Service fail." << endl;
		return false;
	}

	SERVICE_STATUS ServiceStatus;
	Res = ControlService(ServiceHandle, SERVICE_CONTROL_STOP, &ServiceStatus);
	if (!Res) {
		cout << "[StopDriver] Control Service fail." << endl;
		return false;
	}

	Res = DeleteService(ServiceHandle);
	if (!Res) {
		cout << "[StopDriver] Delete Service fail." << endl;
		return false;
	}

	return true;
}