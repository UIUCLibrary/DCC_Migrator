/**
* @file pygmagick.c
* @author hborcher
* @date 2/3/17
*
*/

#include <Python.h>
#include "glue.h"

static PyObject *pygmagickHelloworld(PyObject *self, PyObject *args, PyObject *keywds) {
    char *s = NULL;
    char result[64];
    static char *kwlist[] = {(char *) "name", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, keywds, "|s", kwlist, &s)) {
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


static PyObject *version(PyObject *self) {
    return Py_BuildValue("s", "Version 0.1");
}


static PyMethodDef pygmagickMethods[] = {
        {"hello",   (PyCFunction) pygmagickHelloworld, METH_VARARGS | METH_KEYWORDS, "Hello World."},
        {"convert", (PyCFunction) pyConvert,           METH_VARARGS | METH_KEYWORDS, "Execute conversion."},
        {"version", (PyCFunction) version,             METH_NOARGS, "Returns the version."},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pygmagickModule = {
        PyModuleDef_HEAD_INIT,
        "pygmagick", // name of module
        NULL, // module documentation, may be NULL 
        -1,/* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
        pygmagickMethods // Methods
};

PyMODINIT_FUNC PyInit_pygmagick(void) {
    init_library("");
    return PyModule_Create(&pygmagickModule);
}