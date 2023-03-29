#include "nodes/pg_list.h"
#include "nodes/parsenodes.h"
#include "get_parameter.h"
#include "trans_parameter.h"

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

}