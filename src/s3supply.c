#include <Python.h>
#include <stdio.h>
#include "s3supply.h"
void
_s3_supply_init(void)
{

    pid_t fpid;
    fpid = fork();
    if (fpid == 0) {
        Py_Initialize();
        if (!Py_IsInitialized())
        {
//        return -1; //init python failed
        }
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('./')");
        PyRun_SimpleString("print('s3_supply start!')");
        PyObject *pmodule = PyImport_ImportModule("map_matrix");
        if (!pmodule)
        {
            printf("cannot find call_py.py\n");
//        return -1;
        }
        else
        {
            printf("PyImport_ImportModule success\n");
        }

        PyObject *pfunc = PyObject_GetAttrString(pmodule, "transfer_to_s3");
        if (!pfunc)
        {
            printf("cannot find func\n");
            Py_XDECREF(pmodule);
//        return -1;
        }
        else
        {
            printf("PyObject_GetAttrString success\n");
        }
        PyObject *pArgs = PyTuple_New(0);
        PyObject *pResult = PyObject_CallObject(pfunc, pArgs);
//    FILE *fp = fopen("~/test.txt", "w");
//    fprintf(fp, "Hello world\n");
//    fclose(fp);
        Py_XDECREF(pmodule);
        Py_XDECREF(pfunc);
        Py_XDECREF(pArgs);
        Py_XDECREF(pResult);

        Py_Finalize();
    }
    return;
}