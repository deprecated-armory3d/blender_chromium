/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#include "ArmoryWrapper.h"
#include "simple_app.h"
#include "simple_handler.h"
#if defined(OS_WIN)
#include "include/cef_sandbox_win.h"
#include <windows.h>
#elif defined(OS_LINUX)
#include <X11/Xlib.h>
#else
#include "include/cef_application_mac.h"
#endif
#include "include/wrapper/cef_helpers.h"

char armory_url[512];
char armory_jssource[512];
char armory_console[512];
int armory_console_updated;
char armory_operator[512];
int armory_operator_updated;

void armoryNew() {

#if defined(OS_WIN)
	CefEnableHighDPISupport();
	CefMainArgs main_args(NULL);
#else
	CefMainArgs main_args(0, NULL);
#endif

	if (CefExecuteProcess(main_args, NULL, NULL) > 0) {
		return;
	}

	CefSettings settings;
	settings.no_sandbox = true;
	CefRefPtr<SimpleApp> app(new SimpleApp);
	CefInitialize(main_args, settings, app.get(), NULL);
}

void armoryInit() {
	SimpleApp::CreateNewBrowser();
}

void armoryShow(int x, int y, int w, int h) {
	SimpleHandler::GetInstance()->ShowBrowser(x, y, w, h);
	std::string url(armory_url, strlen(armory_url));
	SimpleHandler::GetInstance()->browser->GetMainFrame()->LoadURL(url);
}

void armoryExit() {
	SimpleHandler::GetInstance()->HideBrowser();
}

void armoryDraw() {
	if (SimpleHandler::GetInstance()->HasFocus()) {
		CefDoMessageLoopWork();
	}
}

void armoryUpdatePosition(int x, int y, int w, int h) {
	SimpleHandler::GetInstance()->UpdatePosition(x, y, w, h);
}

void armoryFree() {
#if defined(OS_WIN) || defined(OS_LINUX)
	CefShutdown();
#endif
}

void armoryCallJS() {
	SimpleHandler::GetInstance()->browser->GetMainFrame()->ExecuteJavaScript(armory_jssource, SimpleHandler::GetInstance()->browser->GetMainFrame()->GetURL(), 0);
}

void armoryLoadUrl() {
	std::string url(armory_url, strlen(armory_url));
	SimpleHandler::GetInstance()->browser->GetMainFrame()->LoadURL(url);
}
