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

/** \file blender/python/barmory/barmory_py_api.c
 *  \ingroup pygen
 *
 * This file defines the 'barmory' module
 */

#include <Python.h>
#include "barmory_py_api.h"
#include "BLI_utildefines.h"
#include "../generic/python_utildefines.h"

#include "../../editors/space_armory/ArmoryWrapper.h"

/*----------------------------MODULE FUNCTIONS-------------------------*/
PyDoc_STRVAR(py_bk_set_url_doc,
".. function:: set_url()\n"
"\n"
"   Set url to be opened.\n"
);
static PyObject *py_bk_set_url(PyObject *UNUSED(self), PyObject *args)
{
	char* name;
	if (!PyArg_ParseTuple(args, "s:barmory.set_url", &name))
		return NULL;

	strcpy(armory_url, name);

	Py_RETURN_NONE;
}

PyDoc_STRVAR(py_bk_load_url_doc,
".. function:: load_url()\n"
"\n"
"   Navigate to currenly set url.\n"
);
static PyObject *py_bk_load_url(PyObject *UNUSED(self), PyObject *args)
{
	armoryLoadUrl();
	Py_RETURN_NONE;
}

PyDoc_STRVAR(py_bk_draw_doc,
".. function:: draw()\n"
"\n"
"   Navigate to currenly set url.\n"
);
static PyObject *py_bk_draw(PyObject *UNUSED(self), PyObject *args)
{
	armoryDraw();
	Py_RETURN_NONE;
}

PyDoc_STRVAR(py_bk_call_js_doc,
".. function:: call_js()\n"
"\n"
"   Call JavaScript function.\n"
);
static PyObject *py_bk_call_js(PyObject *UNUSED(self), PyObject *args)
{
	char* name;
	if (!PyArg_ParseTuple(args, "s:barmory.call_js", &name))
		return NULL;

	strcpy(armory_jssource, name);
	armoryCallJS();

	Py_RETURN_NONE;
}

PyDoc_STRVAR(py_bk_get_console_doc,
".. function:: get_console()\n"
"\n"
"   Read console log.\n"
);
static PyObject *py_bk_get_console(PyObject *UNUSED(self), PyObject *args)
{
	PyObject *pyobj = Py_BuildValue("s", armory_console);
	armory_console_updated = 0;
	return pyobj;
}

PyDoc_STRVAR(py_bk_get_console_updated_doc,
".. function:: get_console_updated()\n"
"\n"
"   Check if console has been written to.\n"
);
static PyObject *py_bk_get_console_updated(PyObject *UNUSED(self), PyObject *args)
{
	PyObject *pyobj = Py_BuildValue("i", armory_console_updated);
	return pyobj;
}


PyDoc_STRVAR(py_bk_get_operator_doc,
".. function:: get_operator()\n"
"\n"
"   Read operator log.\n"
);
static PyObject *py_bk_get_operator(PyObject *UNUSED(self), PyObject *args)
{
	PyObject *pyobj = Py_BuildValue("s", armory_operator);
	armory_operator_updated = 0;
	return pyobj;
}

PyDoc_STRVAR(py_bk_get_operator_updated_doc,
".. function:: get_console_updated()\n"
"\n"
"   Check if operator log has been written to.\n"
);
static PyObject *py_bk_get_operator_updated(PyObject *UNUSED(self), PyObject *args)
{
	PyObject *pyobj = Py_BuildValue("i", armory_operator_updated);
	return pyobj;
}

/*----------------------------MODULE INIT-------------------------*/
static PyMethodDef BK_methods[] = {
	{"set_url", (PyCFunction) py_bk_set_url, METH_VARARGS, py_bk_set_url_doc},
	{"load_url", (PyCFunction) py_bk_load_url, METH_VARARGS, py_bk_load_url_doc},
	{"draw", (PyCFunction) py_bk_draw, METH_VARARGS, py_bk_draw_doc},
	{"call_js", (PyCFunction) py_bk_call_js, METH_VARARGS, py_bk_call_js_doc},
	{"get_console", (PyCFunction) py_bk_get_console, METH_NOARGS, py_bk_get_console_doc},
	{"get_console_updated", (PyCFunction) py_bk_get_console_updated, METH_NOARGS, py_bk_get_console_updated_doc},
	{"get_operator", (PyCFunction) py_bk_get_operator, METH_NOARGS, py_bk_get_operator_doc},
	{"get_operator_updated", (PyCFunction) py_bk_get_operator_updated, METH_NOARGS, py_bk_get_operator_updated_doc},
	{NULL, NULL, 0, NULL}
};

PyDoc_STRVAR(BK_doc,
"This module provides access to armory."
);
static struct PyModuleDef BK_module_def = {
	PyModuleDef_HEAD_INIT,
	"barmory",  /* m_name */
	BK_doc,  /* m_doc */
	0,  /* m_size */
	BK_methods,  /* m_methods */
	NULL,  /* m_reload */
	NULL,  /* m_traverse */
	NULL,  /* m_clear */
	NULL,  /* m_free */
};

PyObject *BPyInit_barmory(void)
{
	PyObject *mod;
	mod = PyModule_Create(&BK_module_def);
	return mod;
}
