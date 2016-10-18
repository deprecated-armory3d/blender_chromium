// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_handler.h"
#include "ArmoryWrapper.h"

#include <sstream>
#include <string>

#include "include/base/cef_bind.h"
#include "include/cef_app.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

namespace {
SimpleHandler* g_instance = NULL;
}

SimpleHandler::SimpleHandler() {
	DCHECK(!g_instance);
	g_instance = this;
}

SimpleHandler::~SimpleHandler() {
	g_instance = NULL;
}

SimpleHandler* SimpleHandler::GetInstance() {
	return g_instance;
}

void SimpleHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) {
	CEF_REQUIRE_UI_THREAD();
}

void SimpleHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser_) {
	CEF_REQUIRE_UI_THREAD();

	// Add to the list of existing browsers.
	browser = browser_;
}

bool SimpleHandler::DoClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();
	// Allow the close. For windowed browsers this will result in the OS close
	// event being sent.

	return false;
}

void SimpleHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
	CEF_REQUIRE_UI_THREAD();

	browser = NULL;
}

void SimpleHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
								CefRefPtr<CefFrame> frame,
								ErrorCode errorCode,
								const CefString& errorText,
								const CefString& failedUrl) {
	CEF_REQUIRE_UI_THREAD();
	// Don't display an error for downloaded files.
	if (errorCode == ERR_ABORTED) {
		return;
	}
	printf("Load error.\n");
}

bool SimpleHandler::OnConsoleMessage(CefRefPtr<CefBrowser> browser,
					  const CefString& message,
					  const CefString& source,
					  int line) {
	CEF_REQUIRE_UI_THREAD();

	if (strlen(message.ToString().c_str()) >= 512) {
		// Message too long, output to console
		printf("%s\n", message.ToString().c_str());
		return;
	}

	int pos = message.ToString().find(" ", 0);
	if (message.ToString().compare(pos + 1, 5, "__arm") == 0) {
		strcpy(armory_operator, message.ToString().c_str());
		armory_operator_updated = 1;
	}
	else {
		if (armory_console_updated == 1) {
			// Message was not read from Python, output to console before overwriting
			printf("%s\n", armory_console);
		}

		strcpy(armory_console, message.ToString().c_str());
		armory_console_updated = 1;
	}
}
