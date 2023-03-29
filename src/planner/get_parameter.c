#include <postgres.h>
#include <nodes/nodes.h>
#include <nodes/pg_list.h>
#include <nodes/parsenodes.h>
#include <stringinfo.h>
#include <Python.h>

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
//        return 1;
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
//        return 1;
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

void
query_to_string(Query *query)
{
    // init attr_name
    StringInfoData attr_name;
    initStringInfo(&attr_name);

    // init table_name
    StringInfoData table_name;
    initStringInfo(&table_name);

    // init where condition
    StringInfoData where_part;
    initStringInfo(&where_part);

//    appendStringInfoString(&buf, "SELECT ");

    ListCell *lc;
    foreach (lc, query->targetList)
    {
        TargetEntry *te = (TargetEntry *) lfirst(lc);
        appendStringInfoString(&attr_name, te->resname);
        if (lc->next != NULL)
            appendStringInfoString(&attr_name, ",");
    }

//    appendStringInfoString(&buf, " FROM ");

    RangeTblEntry *rte = (RangeTblEntry *) linitial(query->rtable);
    appendStringInfoString(&table_name, rte->eref->aliasname);

    if (query->jointree != NULL && query->jointree->quals != NULL)
    {
//        appendStringInfoString(&buf, " WHERE ");
        Node *quals = query->jointree->quals;
        char *quals_str = nodeToString(quals);
        appendStringInfoString(&where_part, quals_str);
        pfree(quals_str);
    }

//    if (query->limitCount > 0)
//        appendStringInfo(&buf, " LIMIT %d", query->limitCount);

//    char *result = buf.data;
    char *attr_name_str = attr_name.data;
    char *table_name_str = table_name.data;
    char *where_part_str = where_part.data;
    trans_parameter(attr_name_str,table_name_str,where_part_str);

}