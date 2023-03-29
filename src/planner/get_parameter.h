//
// Created by 徐涛 on 2023/3/29.
//
#include "nodes/pg_list.h"
#include "nodes/parsenodes.h"
#include <Python.h>


#ifndef TSDB_FYP_GET_PARAMETER_H
#define TSDB_FYP_GET_PARAMETER_H

#endif //TSDB_FYP_GET_PARAMETER_H

void
trans_parameter(char* str1, char* str2, char* str3);

void
query_to_string(Query *query);