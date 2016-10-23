// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_handler.h"

#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"

void SimpleHandler::PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) {

}

void SimpleHandler::WindowInfoSetAsChild(CefWindowInfo *window_info) {

}

void SimpleHandler::ShowBrowser(int x, int y, int w, int h) {
	CEF_REQUIRE_UI_THREAD();
	
}

void SimpleHandler::HideBrowser() {
	CEF_REQUIRE_UI_THREAD();
	
}

void SimpleHandler::FinishLaunching() {
	
}
