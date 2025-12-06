#ifndef CURSOR_H
#define CURSOR_H

#include "table.h"
#include <stdbool.h>

typedef struct {
  Table *table;
  uint32_t page_num;
  uint32_t cell_num;
  bool end_of_table;
} Cursor;

/*
 * @returns a cursor to the beginning of the table
 */
Cursor *table_start(Table *table);

/*
 * @returns a cursor to the end of the table
 */
Cursor *table_end(Table *table);

/*
 * @returns a pointer to the position described by the cursor
 */
void *cursor_value(Cursor *cursor);

/*
 * @move the cursor forward
 */
void cursor_advance(Cursor *cursor);

#endif // !CURSOR_H
