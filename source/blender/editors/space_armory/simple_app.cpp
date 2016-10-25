// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_app.h"
#include <string>
#include "simple_handler.h"
#include "ArmoryWrapper.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_helpers.h"

SimpleApp::SimpleApp() { }

CefRefPtr<SimpleHandler> handler;

void SimpleApp::OnContextInitialized() {
	CEF_REQUIRE_UI_THREAD();

	// SimpleHandler implements browser-level callbacks.
	handler = CefRefPtr<SimpleHandler>(new SimpleHandler());

// #if !defined(OS_WIN) && !defined(OS_LINUX)
	CefDoMessageLoopWork(); // Calls finishLaunching on its own?
	// handler->FinishLaunching();
// #endif
}

void SimpleApp::CreateNewBrowser() {
	CEF_REQUIRE_UI_THREAD();

	CefBrowserSettings browser_settings;
	browser_settings.file_access_from_file_urls = STATE_ENABLED;
	browser_settings.application_cache = STATE_DISABLED;

	CefWindowInfo windowInfo;
	SimpleHandler::GetInstance()->WindowInfoSetAsChild(&windowInfo);
	CefBrowserHost::CreateBrowserSync(windowInfo, SimpleHandler::GetInstance(), "about:blank", browser_settings, NULL);
}

void SimpleApp::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line) {
	// CefString noplug(L"disable-plugins"); 
	// command_line->AppendSwitch(noplug);
}
