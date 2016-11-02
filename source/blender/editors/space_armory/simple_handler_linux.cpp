// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "simple_handler.h"

#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"
#include <X11/Xlib.h>

namespace {
	Display *d;

	int XErrorHandlerImpl(Display *display, XErrorEvent *event) {
		return 0;
	}

	int XIOErrorHandlerImpl(Display *display) {
		return 0;
	}

	Window get_top_window(Display* d, Window start){
	  Window w = start;
	  Window parent = start;
	  Window root = None;
	  Window *children;
	  unsigned int nchildren;
	  Status s;

	  while (parent != root) {
	    w = parent;
	    s = XQueryTree(d, w, &root, &parent, &children, &nchildren); // see man

	    if (s)
	      XFree(children);

	  }
	  return w;
	}

	Window get_focus_window(Display* d){
	  Window w;
	  int revert_to;
	  XGetInputFocus(d, &w, &revert_to); // see man
	  return w;
	}

	int lastw, lasth;
}

void SimpleHandler::PlatformTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) {

}

void SimpleHandler::WindowInfoSetAsChild(CefWindowInfo *window_info) {

	XSetErrorHandler(XErrorHandlerImpl);
	XSetIOErrorHandler(XIOErrorHandlerImpl);

	d = cef_get_xdisplay();

	Window winroot = get_focus_window(d);
	winroot = get_top_window(d, winroot);

	CefRect rect(0, 0, 0, 0);
	window_info->SetAsChild(winroot, rect);
}

void SimpleHandler::ShowBrowser(int x, int y, int w, int h) {
	CEF_REQUIRE_UI_THREAD();

	Window cwin = browser->GetHost()->GetWindowHandle();
	XMapWindow(d, cwin);

	SimpleHandler::UpdatePosition(x, y, w, h);	
}

void SimpleHandler::HideBrowser() {
	CEF_REQUIRE_UI_THREAD();

	Window cwin = browser->GetHost()->GetWindowHandle();
	XUnmapWindow(d, cwin);
	
}

void SimpleHandler::FinishLaunching() {
	
}

void SimpleHandler::UpdatePosition(int x, int y, int w, int h) {

	Window cwin = browser->GetHost()->GetWindowHandle();
	
	Window winroot = get_focus_window(d);
	winroot = get_top_window(d, winroot);
	unsigned int parentW = 0;
	unsigned int parentH = 0;
	unsigned int borderw = 0;
	unsigned int depthret = 0;
	Window rw;
	int rx, ry;
	XGetGeometry(d, winroot, &rw, &rx, &ry, &parentH, &parentH, &borderw, &depthret);

	XMoveResizeWindow(d, cwin, x + 11, (parentH - y - h) - 11, w, h);

	lastw = w;
	lasth = h;
}

bool SimpleHandler::HasFocus() {
	// Set input
	Window winroot = get_focus_window(d);
	winroot = get_top_window(d, winroot);

	Window cwin = browser->GetHost()->GetWindowHandle();


	Window rw;
	Window cw;
	unsigned int maskret;
	int rx, ry, wx, wy;
	XQueryPointer(d, cwin, &rw, &cw, &rx, &ry, &wx, &wy, &maskret);

	if (wx < 0 || wy < 0 || wx > lastw || wy > lasth) {
		XSetInputFocus(d, winroot, RevertToNone, CurrentTime);
	}
	// else - Takes input back automatically

	return true;
}