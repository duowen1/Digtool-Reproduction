#include <iostream>
#include <string>
using namespace std;

string GetCpuID();
bool VMX_Support_Detection();

bool HardwareCheck() {
	string CpuID;
	CpuID = GetCpuID();
	if (CpuID != "GenuineIntel") {
		cout << "[HardwareCheck]This program is not designed to run in a non-VT-x environemnt !" << endl;
		return false;
	}


	bool Res;
	Res = VMX_Support_Detection();
	if (!Res) {
		cout << "[HardwareCheck]VMX Operation is not supported by your processor." << endl;
		return Res;
	}

	return true;
}


string GetCpuID() {
	char SysType[13]; //Array consisting of 13 single bytes/characters
	string CpuID; //The string that will be used to add all the characters to
	
	//Starting coding in assembly language
	_asm
	{
		//Execute CPUID with EAX = 0 to get the CPU producer
		XOR EAX, EAX
		CPUID
		//MOV EBX to EAX and get the characters one by one by using shift out right bitwise operation.
		MOV EAX, EBX
		MOV SysType[0], al
		MOV SysType[1], ah
		SHR EAX, 16
		MOV SysType[2], al
		MOV SysType[3], ah
		//Get the second part the same way but these values are stored in EDX
		MOV EAX, EDX
		MOV SysType[4], al
		MOV SysType[5], ah
		SHR EAX, 16
		MOV SysType[6], al
		MOV SysType[7], ah
		//Get the third part
		MOV EAX, ECX
		MOV SysType[8], al
		MOV SysType[9], ah
		SHR EAX, 16
		MOV SysType[10], al
		MOV SysType[11], ah
		MOV SysType[12], 00
	}
	CpuID.assign(SysType, 12);
	return CpuID;
}

bool VMX_Support_Detection()
{
	bool VMX = false;
	__asm {
		xor eax, eax
		inc    eax
		cpuid
		bt     ecx, 0x5
		jc     VMXSupport
		VMXNotSupport :
		jmp     NopInstr
		VMXSupport :
		mov    VMX, 0x1
		NopInstr :
		nop
	}
	return VMX;
}
