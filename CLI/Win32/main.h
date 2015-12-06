#pragma once
#include "resource.h"

struct ControlHandler {
	WNDPROC previousProc;
	virtual INT_PTR windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

extern void setHandlerForControl(HWND control, shared_ptr<ControlHandler> handler);

template<typename T>
unique_ptr<T> make_unique(T *value) {
	return unique_ptr<T>(value);
}
template<typename T>
shared_ptr<T> make_shared(T *value) {
	return shared_ptr<T>(value);
}

extern HWND g_hDlgCurrent;
