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

#ifndef ARMORY_WRAPPER_H
#define ARMORY_WRAPPER_H

#ifdef __cplusplus
     extern "C" {
#endif

    void armoryNew(void);
    void armoryInit();
    void armoryShow(int x, int y, int w, int h);
    void armoryExit(void);
    void armoryDraw(void);
    void armoryFree(void);
    bool armoryStarted(void);
    void armoryUpdatePosition(int x, int y, int w, int h);

    void armoryCallJS();
    void armoryLoadUrl();
    void armoryUpdateChromium();

    extern char armory_url[512]; // Passed from Python
    extern char armory_jssource[512];
    extern char armory_console[512];
	extern int armory_console_updated;
    extern char armory_operator[512];
    extern int armory_operator_updated;

#ifdef __cplusplus
    }
#endif

#endif
