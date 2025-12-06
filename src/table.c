#include "table.h"
#include "btree.h"
#include <stdio.h>
#include <unistd.h>

Table *db_open(const char *filename) {
  Pager *pager = pager_open(filename);
  uint32_t num_rows = pager->file_length / ROW_SIZE;
  Table *table = malloc(sizeof(Table));
  table->pager = pager;
  table->root_page_num = 0;
  if (pager->num_pages == 0) {
    // new db file
    void *root_node = get_page(pager, 0);
    initialize_leaf_node(root_node);
  }
  return table;
}

void *row_slot(Table *table, uint32_t row_num) {
  uint32_t page_num = row_num / ROWS_PER_PAGE;
  void *page = get_page(table->pager, page_num);
  uint32_t row_offset = row_num % ROWS_PER_PAGE;
  uint32_t byte_offset = row_offset * ROW_SIZE;
  return page + byte_offset;
}

ExecuteResult execute_insert(Statement *statement, Table *table) {
  void *node = get_page(table->pager, table->root_page_num);
  if ((*leaf_node_num_cells(node) >= LEAF_NODE_MAX_CELLS)) {
    return EXECUTE_TABLE_FULL;
  }
  Row *row_to_insert = &(statement->row_to_insert);
  Cursor *cursor = table_end(table);
  leaf_node_insert(cursor, row_to_insert->id, row_to_insert);
  free(cursor);
  return EXECUTE_SUCCESS;
}

void db_close(Table *table) {
  Pager *pager = table->pager;
  for (uint32_t i = 0; i < pager->num_pages; i++) {
    if (pager->pages[i] == NULL) {
      continue;
    }
    pager_flush(pager, i);
    free(pager->pages[i]);
    pager->pages[i] = NULL;
  }
  int result = close(pager->file_descriptor);
  if (result == -1) {
    printf("Error closing db file.\n");
    exit(EXIT_FAILURE);
  }
  for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
    void *page = pager->pages[i];
    if (page) {
      free(page);
      pager->pages[i] = NULL;
    }
  }
  free(pager);
  free(table);
}

ExecuteResult execute_select(Table *table) {
  Cursor *cursor = table_start(table);
  Row row;
  for (uint32_t i = 0; i < table->num_rows; i++) {
    deserialize_row(row_slot(table, i), &row);
    print_row(&row);
  }
  while (!(cursor->end_of_table)) {
    deserialize_row(cursor_value(cursor), &row);
    print_row(&row);
    cursor_advance(cursor);
  }
  free(cursor);
  return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement *statement, Table *table) {
  switch (statement->type) {
  case (STATEMENT_INSERT):
    return execute_insert(statement, table);
  case (STATEMENT_SELECT):
    return execute_select(table);
  }
}
