//
// Created by Borchers, Henry Samuel on 2/8/17.
//

/**
* @file migrate.c
* @author hborcher
* @date 2/8/17
*
*/

#include <Python.h>
//#include "metadata.h"
#include "metadata_pyglue.h"

PyObject *migrateHelloWorld(PyObject *self, PyObject *args, PyObject *kwargs) {
    char *s = NULL;
    char result[64];
    static char *kwlist[] = {"name", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|s", kwlist, &s)) {
        return NULL;
    }
    if (NULL == s) {
        return Py_BuildValue("s", "Hello world from C exiv2py!");
    } else {
        strcpy(result, "Hello, ");
        strcat(result, s);
        return Py_BuildValue("s", result);
    }
}




PyObject *version(PyObject *self) {
    return Py_BuildValue("s", "Version 0.1");
}


static PyMethodDef migrateMethods[] = {
        {"hello",         (PyCFunction) migrateHelloWorld, METH_VARARGS | METH_KEYWORDS, "Hello World."},
        {"version",       (PyCFunction) version,           METH_NOARGS, "Returns the version."},
        {"read_metadata", (PyCFunction) py_read_data,      METH_VARARGS | METH_KEYWORDS, "reads metadata"},
        {NULL, NULL, 0,                                                                  NULL}
};

static struct PyModuleDef migrateModule = {
        PyModuleDef_HEAD_INIT,
        "migrate", // name of module
        NULL, // module documentation, may be NULL
        -1,/* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
        migrateMethods // Methods
};

PyMODINIT_FUNC PyInit_exiv2py(void) {
    return PyModule_Create(&migrateModule);
}