#include "stdafx.h"
#include "DialogHandler.h"
#pragma comment(linker, \
	"\"/manifestdependency:type='Win32' "\
	"name='Microsoft.Windows.Common-Controls' "\
	"version='6.0.0.0' "\
	"processorArchitecture='*' "\
	"publicKeyToken='6595b64144ccf1df' "\
	"language='*'\"")
#pragma comment(lib, "ComCtl32.lib")

HWND g_hDlgCurrent;
static unique_ptr<DialogHandler> winHandler;
static map<HWND, shared_ptr<ControlHandler>> handlers;

static INT_PTR CALLBACK MainWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == WM_INITDIALOG) {
		winHandler = make_unique(new DialogHandler(hDlg));
	}
	if (winHandler) {
		return winHandler->windowProc(message, wParam, lParam);
	}
	return (INT_PTR) FALSE;
}

static INT_PTR CALLBACK ControlCallbackProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	return handlers[hDlg]->windowProc(hDlg, message, wParam, lParam);
}

void setHandlerForControl(HWND control, shared_ptr<ControlHandler> handler) {
	handlers[control] = handler;
	handler->previousProc = (WNDPROC) SetWindowLongPtr(control, GWL_WNDPROC, (LONG_PTR) &ControlCallbackProc);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR	lpCmdLine,
					   int	   nCmdShow) {
	MSG msg;
	HACCEL hAccelTable;

#ifdef _DEBUG
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	InitCommonControls();
	LoadLibrary(L"riched20.dll");
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLI));

	HWND hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINFORM), NULL, MainWndProc);
	ShowWindow(hDlg, SW_SHOW);

	// Main message loop:
	while (GetMessage(&msg, 0, 0, 0)) {
		if (!TranslateAccelerator(hDlg, hAccelTable, &msg)) {
			if (winHandler) {
				winHandler->onIdle();
				// To allow for scrolling on hover
				if (msg.message == WM_MOUSEWHEEL) {
					POINT pos = {msg.lParam & 0xffff, msg.lParam >> 16};
					HWND hWnd = WindowFromPoint(pos);
					if (hWnd && hWnd != msg.hwnd) {
						SendMessage(hWnd, msg.message, msg.wParam, msg.lParam);
						continue;
					}
				}
			}
			// Normal processing
			if (!g_hDlgCurrent || !IsDialogMessage(g_hDlgCurrent, &msg)) {
				TranslateMessage(&msg);		// translate virtual-key messages
				DispatchMessage(&msg);		// send it to dialog procedure
			}
		}
	}
	return (int) msg.wParam;
}
