// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_handler.h"

#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"
#include <Windows.h>

void SimpleHandler::PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) {

}

void SimpleHandler::WindowInfoSetAsChild(CefWindowInfo *window_info) {

	window_info->SetAsChild(GetActiveWindow(), 0, 0, 0, 0);
}

void SimpleHandler::ShowBrowser(int x, int y, int w, int h) {
	CEF_REQUIRE_UI_THREAD();
	
	float scale = 1.0;

	HWND* view = browser->GetHost()->GetWindowHandle();
	SetWindowPos(view, HWND_TOP, x / scale, y / scale, w / scale, h / scale, SWP_SHOWWINDOW)

	SetParent(view, GetActiveWindow());

}

void SimpleHandler::HideBrowser() {
	CEF_REQUIRE_UI_THREAD();
	
	HWND* view = browser->GetHost()->GetWindowHandle();
	ShowWindow(view, SW_HIDE);
}

void SimpleHandler::FinishLaunching() {
	
}
