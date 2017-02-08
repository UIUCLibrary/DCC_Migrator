/**
* @file migrate.c
* @author hborcher
* @date 2/8/17
*
*/

#include <Python.h>
#include "convert.h"
#include "metadata.h"

// *******************************************************************************
PyObject *migrateHelloWorld(PyObject *self, PyObject *args, PyObject *kwargs) {
    char *s = NULL;
    char result[64];
    static char *kwlist[] = {"name", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|s", kwlist, &s)) {
        return NULL;
    }
    if (NULL == s) {
        return Py_BuildValue("s", "Hello world from C extension!");
    } else {
        strcpy(result, "Hello, ");
        strcat(result, s);
        return Py_BuildValue("s", result);
    }
}


PyObject *version(PyObject *self) {
    return Py_BuildValue("s", "Version 0.1");
}
// *******************************************************************************
// Conversion Methods
static PyObject *pyConvert(PyObject *self, PyObject *args, PyObject *kwargs) {
    char *input = NULL;
    char *output = NULL;
    static PyObject *my_error;

    static char *kwlist[] = {
            (char *) "input",
            (char *) "output",
            NULL
    };

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ss", kwlist, &input, &output)) {
        return NULL;
    }
    if (convert(input, output) != 0) {
        puts("Failing");

        my_error = PyErr_NewException("pymagick.convert", NULL, NULL);
        PyErr_SetString(my_error, get_error_str());
        return NULL;
    }

    Py_RETURN_NONE;
}

// *******************************************************************************
// Metadata Methods
static PyObject *py_read_data(PyObject *self, PyObject *args, PyObject *kwargs) {
    char *source = NULL;
    static char *kwlist[] = {"name", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s", kwlist, &source)) {
        return NULL;
    }
    read_data(source);

    Py_RETURN_NONE;
}


// *******************************************************************************
// Registration functions
static PyMethodDef migrateMethods[] = {
        {"hello",         (PyCFunction) migrateHelloWorld, METH_VARARGS | METH_KEYWORDS, "Hello World."},
        {"version",       (PyCFunction) version,           METH_NOARGS, "Returns the version."},
        {"read_metadata", (PyCFunction) py_read_data,      METH_VARARGS | METH_KEYWORDS, "reads metadata"},
        {"convert", (PyCFunction) pyConvert,           METH_VARARGS | METH_KEYWORDS, "Execute conversion."},
        {"version", (PyCFunction) version,             METH_NOARGS, "Returns the version."},
        {NULL, NULL, 0,                                                                  NULL}
};

static struct PyModuleDef migrateModule = {
        PyModuleDef_HEAD_INIT,
        "migrate", // name of module
        NULL, // module documentation, may be NULL
        -1,/* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
        migrateMethods // Methods
};

PyMODINIT_FUNC PyInit_migrate(void) {
    return PyModule_Create(&migrateModule);
}