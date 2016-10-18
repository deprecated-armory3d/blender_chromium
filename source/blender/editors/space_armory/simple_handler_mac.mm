// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_handler.h"

#import <Cocoa/Cocoa.h>

#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"

void SimpleHandler::PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) {

}

void SimpleHandler::WindowInfoSetAsChild(CefWindowInfo *window_info) {
	window_info->SetAsChild([[[NSApplication sharedApplication] mainWindow] contentView], 0, 0, 0, 0);
}

void SimpleHandler::ShowBrowser(int x, int y, int w, int h) {
	CEF_REQUIRE_UI_THREAD();
	float scale = [[[NSApplication sharedApplication] mainWindow] backingScaleFactor];
	if (scale == 0.0) scale = 1.0;

	NSView* view = browser->GetHost()->GetWindowHandle();
	NSRect newFrame = CGRectMake(x / scale, y / scale, w / scale, h / scale);
	[view setFrame:newFrame];

	[[[[NSApplication sharedApplication] mainWindow] contentView] addSubview:view];
}

void SimpleHandler::HideBrowser() {
	CEF_REQUIRE_UI_THREAD();
	
	// NSView* view = browser->GetHost()->GetWindowHandle();
	// NSRect newFrame = CGRectMake(0, 0, 0, 0);
	// [view setFrame:newFrame];

	NSView* view = browser->GetHost()->GetWindowHandle();
	[view removeFromSuperview];
}

void SimpleHandler::FinishLaunching() {
	[NSApp finishLaunching];
}
