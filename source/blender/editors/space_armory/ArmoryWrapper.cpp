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
#include "include/cef_application_mac.h"
#include "include/wrapper/cef_helpers.h"

char armory_url[512];
char armory_jssource[512];
char armory_console[512];
int armory_console_updated;
char armory_operator[512];
int armory_operator_updated;

void armoryNew() {
	CefMainArgs main_args(0, NULL);
	CefSettings settings;
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
	SimpleHandler::GetInstance()->browser->GetMainFrame()->LoadURL("about:blank");
}

void armoryDraw() {
	CefDoMessageLoopWork();
}

void armoryCallJS() {
	SimpleHandler::GetInstance()->browser->GetMainFrame()->ExecuteJavaScript(armory_jssource, SimpleHandler::GetInstance()->browser->GetMainFrame()->GetURL(), 0);
}

void armoryLoadUrl() {
	std::string url(armory_url, strlen(armory_url));
	SimpleHandler::GetInstance()->browser->GetMainFrame()->LoadURL(url);
}
