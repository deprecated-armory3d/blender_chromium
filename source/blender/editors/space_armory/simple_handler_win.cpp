// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_handler.h"

#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"
#include <Windows.h>

namespace {
	HWND mainWindow;
	bool resizing = false;
}

void SimpleHandler::PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) {

}

void SimpleHandler::WindowInfoSetAsChild(CefWindowInfo *window_info) {

	mainWindow = GetActiveWindow();

	RECT rect = { 0 };
	window_info->SetAsChild(GetActiveWindow(), rect);
}

float dpiScale = 1.0;
void SimpleHandler::ShowBrowser(int x, int y, int w, int h) {
	CEF_REQUIRE_UI_THREAD();
	
	// SetProcessDPIAware(); //true
	HDC screen = GetDC(NULL);
	double hPixelsPerInch = GetDeviceCaps(screen,LOGPIXELSX);
	double vPixelsPerInch = GetDeviceCaps(screen,LOGPIXELSY);
	ReleaseDC(NULL, screen);
	dpiScale = ((hPixelsPerInch + vPixelsPerInch) * 0.5) / 96;

	//float scale = 1.0;

	HWND view = browser->GetHost()->GetWindowHandle();

	RECT r;
	GetWindowRect(mainWindow, &r);
	int parentH = r.bottom - r.top;

	// HMONITOR monitor = MonitorFromWindow(mainWindow, MONITOR_DEFAULTTONEAREST);
	// MONITORINFO info;
	// info.cbSize = sizeof(MONITORINFO);
	// GetMonitorInfo(monitor, &info);
	// int monitor_height = info.rcMonitor.bottom - info.rcMonitor.top;

	int offset = 5 + 4 * dpiScale;// 9;//14;

	SetWindowPos(view, HWND_TOP, r.left + x + offset, r.top + (parentH - y - h) - offset, w, h, SWP_SHOWWINDOW);

}

void SimpleHandler::UpdatePosition(int x, int y, int w, int h) {
	RECT r;
	GetWindowRect(mainWindow, &r);
	int parentH = r.bottom - r.top;

	int offset = 5 + 4 * dpiScale;// 9;//14;
	HWND view = browser->GetHost()->GetWindowHandle();
	SetWindowPos(view, HWND_TOP, r.left + x + offset, r.top + (parentH - y - h) - offset, w, h, SWP_SHOWWINDOW);
}

void SimpleHandler::HideBrowser() {
	CEF_REQUIRE_UI_THREAD();
	
	HWND view = browser->GetHost()->GetWindowHandle();
	ShowWindow(view, SW_HIDE);
}

void SimpleHandler::FinishLaunching() {
	
}

bool SimpleHandler::HasFocus() {
	RECT r;
	GetWindowRect(mainWindow, &r);

	if (resizing) {
		if (GetKeyState(VK_LBUTTON) < 0) {
			return false;
		}
		else {
			resizing = false;
			return false;
		}
	}
	POINT p;
	if (GetCursorPos(&p)) {
		if (p.x <= r.left + 50 || p.x >= r.right - 50 || p.y >= r.bottom - 50 || p.y <= r.top + 50) {
			if (GetKeyState(VK_LBUTTON) < 0) {
				resizing = true;
				return false;
			}
		}
	}

	return true;
}
