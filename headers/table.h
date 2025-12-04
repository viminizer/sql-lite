#ifndef TABLE_H
#define TABLE_H

#include "pager.h"
#include "result.h"
#include "statement.h"

typedef struct {
  uint32_t num_rows;
  Pager *pager;
} Table;

Table *db_open(const char *filename);
void db_close(Table *table);
ExecuteResult execute_insert(Statement *statement, Table *table);
void *row_slot(Table *table, uint32_t row_num);
ExecuteResult execute_select(Table *table);
ExecuteResult execute_statement(Statement *statement, Table *table);
#endif // TABLE_H
