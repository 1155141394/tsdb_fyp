//
// Created by 徐涛 on 2023/3/29.
//
#include <Python.h>
#include <stdio.h>
#include "trans_parameter.h"

void
trans_parameter(char* str1, char* str2, char* str3){
    // Initialize Python interpreter
    Py_Initialize();

    // Build the name object for the module and function
    PyObject* moduleName = PyUnicode_FromString("query");
    PyObject* functionName = PyUnicode_FromString("query");

    // Import the module
    PyObject* module = PyImport_Import(moduleName);
    if (module == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to import module.\n");
        return 1;
    }

    // Build the argument list
    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, PyUnicode_FromString(str1));
    PyTuple_SetItem(args, 1, PyUnicode_FromString(str2));
    PyTuple_SetItem(args, 2, PyUnicode_FromString(str3));

    // Call the function and get the result
    PyObject* result = PyObject_CallObject(PyObject_GetAttrString(module, "query"), args);
    if (result == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to call function.\n");
        return 1;
    }

    // Print the result
    printf("Result: %s\n", PyUnicode_AsUTF8(result));

    // Clean up
    Py_DECREF(args);
    Py_DECREF(result);
    Py_DECREF(moduleName);
    Py_DECREF(functionName);
    Py_DECREF(module);

    // Shut down Python interpreter
    Py_Finalize();

}