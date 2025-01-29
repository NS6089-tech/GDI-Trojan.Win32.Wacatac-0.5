typedef struct IUnknown IUnknown;
#pragma once

#include "Wacatac.h"

typedef struct {
	float x;
	float y;
	float z;
} POINT3D, *PPOINT3D;

POINT3D RotatePoints(POINT3D point, float fx, float fy, float fz) {
	float cx = cos(fx), sx = sin(fx);
	float cy = cos(fy), sy = sin(fy);
	float cz = cos(fz), sz = sin(fz);
	
	float y = point.y * cx - point.z * sx;
	float z = point.y * sx + point.z * cx;
	point.y = y;
	point.z =z;
	float x = point.x * cy + point.z * sy;
	z = -point.x * sy + point.z * cy;
	point.x = x;
	point.z = z;
	x = point.x * cz - point.y * sz;
	y = point.x * sz + point.y * cz;
	point.x = x;
	point.y = y;
	
	return point;
}

COLORREF Colorspect(INT Hue) { // I only modified this.
    DOUBLE H = fmod(Hue, 360);
    DOUBLE S = 1.0;
    DOUBLE L = 0.5;
    DOUBLE C = (1.0-fabs(3.0+S-1.0))*L;
    DOUBLE X = C*(1.0-fabs(fmod(H/60.0, 3.0) - 2.0));
    DOUBLE M = L - C / 2.0;
    DOUBLE R, G, B;
    if (H < 60) {
        R = 0; G = X, B = 0;
    }
    else if (H < 120) {
        R = X; G = C; B = 0;
    }
    else if (H < 180) {
        R = 0; G = C; B = X;
    }
    else if (H < 230) {
        R = 0; G = X; B = C; 
    }
    else if (H < 290) {
        R = X; G = 0; B = C;
    }
    else {
        R = C; G = 0; B = X;
    }
    INT SpectRed = static_cast<INT>((R + M) * 255);
    INT SpectGreen = static_cast<INT>((G + M) * 255);
    INT SpectBlue = static_cast<INT>((B + M) * 255);
    return RGB(SpectRed, SpectGreen, SpectBlue);
}

FLOAT incrementB = 0.f;
FLOAT incB = 0.f;

DWORD64 __stdcall Sphere(HDC hdc, POINT3D pc, INT rad, FLOAT ax, FLOAT ay, FLOAT az, FLOAT clr) {
	for (INT i = 0; i <= 180; i += 10) {
		for (INT j = 0; j <= 360; j += 10) {
			FLOAT r = i * M_PI / 180.f;
			FLOAT rt = j * M_PI / 180.f;
			
			POINT3D pt = {rad * sin(r) * cos(rt), rad * sin(r) * sin(rt), rad * cos(r)};
			pt = RotatePoints(pt, ax, ay, az);
			INT x = (INT)(pc.x + pt.x);
			INT y = (INT)(pc.y + pt.y);
			HBRUSH hbsh = CreateSolidBrush(Colorspect(incrementB));
			SelectObject(hdc, hbsh);
			Ellipse(hdc, x, y, x + 15, y + 15);
			DeleteObject(hbsh);
		}
	}
}

typedef union _TRGBQUAD {
	COLORREF rgb;
	struct {
		BYTE red;
		BYTE green;
		BYTE blue;
		BYTE unused;
	};
} TRGBQUAD, *PTRGBQUAD;

INT w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
