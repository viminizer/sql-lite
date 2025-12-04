#ifndef STATEMENT_H
#define STATEMENT_H

#include "buffer.h"
#include "result.h"
#include "row.h"

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
  StatementType type;
  Row row_to_insert;
} Statement;

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement);

#endif
