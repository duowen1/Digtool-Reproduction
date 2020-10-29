#include <windows.h>
using namespace std;

HANDLE InitCommunicate();

HANDLE InitCommunicate() {
	return NULL;
	/*
	return CreateFile(
		"\\\\.\\MyHypervisorDevice",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,
		NULL, /// lpSecurityAttirbutes
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_OVERLAPPED,
		NULL);*/
}