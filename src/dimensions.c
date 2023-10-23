#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "dimensions.h"

const char *thing;

static PyObject *
dimensions_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return PyLong_FromLong(sts);
}

static PyObject *
dimensions_save(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, "s", &thing))
        return NULL;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
dimensions_load(PyObject *self, PyObject *args)
{
    return PyUnicode_FromString(thing);
}

static PyMethodDef SpamMethods[] = {
    {"system",  dimensions_system, METH_VARARGS, "Execute a shell command."},
    {"save",  dimensions_save, METH_VARARGS, "Save value"},
    {"load",  dimensions_load, METH_VARARGS, "Load value"},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef dimensionsmodule = {
    PyModuleDef_HEAD_INIT,
    "dimensions",   /* name of module */
    NULL, /*dimensions_doc,  module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    SpamMethods
};

PyMODINIT_FUNC
PyInit_dimensions(void)
{
    return PyModule_Create(&dimensionsmodule);
}

int
main(int argc, char *argv[])
{
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    /* Add a built-in module, before Py_Initialize */
    if (PyImport_AppendInittab("dimensions", PyInit_dimensions) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }
    /* Add a built-in module, before Py_Initialize */
    if (PyImport_AppendInittab("dimensions", PyInit_fraction) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);

    /* Initialize the Python interpreter.  Required.
       If this step fails, it will be a fatal error. */
    Py_Initialize();

    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */
    PyObject *pmodule = PyImport_ImportModule("dimensions");
    if (!pmodule) {
        PyErr_Print();
        fprintf(stderr, "Error: could not import module 'dimensions'\n");
    }

    PyMem_RawFree(program);
    return 0;
}