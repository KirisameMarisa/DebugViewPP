#include "stdafx.h"
#include "windows.h"
#include <string>

#include "Win32/gdi.h"
#include "gdi.h"

namespace fusion
{

void DoPaint(graphics::DeviceContextEx dc)
{
	int y = 60;

	auto grey = RGB(160, 160, 170);
	dc.DrawTimeline(L"Move Sequence", 15, y, 500, grey);
	dc.DrawFlag(L"tag", 200, y);
	dc.DrawFlag(L"tag", 250, y);
	dc.DrawSolidFlag(L"tag", 260, y, RGB(255, 0, 0), RGB(0, 255, 0));
	dc.DrawFlag(L"tag", 270, y);

	dc.DrawTimeline(L"Arbitrary data", 15, 90, 500, grey);
	dc.DrawFlag(L"blueFlag", 470, 90, RGB(0, 0, 255), true);
}

PAINTSTRUCT ps;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		//SetTimer(hwnd, 10, 250, NULL);
		break;

	case WM_PAINT:
		BeginPaint(hwnd, &ps);
		DoPaint(graphics::DeviceContextEx(GetWindowDC(hwnd)));
		EndPaint(hwnd, &ps);
		break;

	case WM_TIMER:
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	using namespace fusion::graphics;

	Window window(hInstance, fusion::WndProc, L"MyClass", L"My window title", 1000, 500);
	window.Show(nCmdShow);

	MessageLoop messageLoop;
	return messageLoop.run();
}
