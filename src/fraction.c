#define PY_SSIZE_T_CLEAN
#include <Python.h>

typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
} FractionObject;

static PyTypeObject FractionType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "fraction.Fraction",
    .tp_doc = PyDoc_STR("Fraction objects"),
    .tp_basicsize = sizeof(FractionObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
};

static PyModuleDef fractionmodule = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "fraction",
    .m_doc = "Example module that creates an extension type.",
    .m_size = -1,
};

PyMODINIT_FUNC
PyInit_fraction(void)
{
    PyObject *m;
    if (PyType_Ready(&FractionType) < 0)
        return NULL;

    m = PyModule_Create(&fractionmodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&FractionType);
    if (PyModule_AddObject(m, "Fraction", (PyObject *) &FractionType) < 0) {
        Py_DECREF(&FractionType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
