#ifndef RESULT_H
#define RESULT_H

#include "buffer.h"
typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_UNRECOGNIZED_STATEMENT,
  PREPARE_SYNTAX_ERROR,
  PREPARE_STRING_TOO_LONG,
  PREPARE_NEGATIVE_ID
} PrepareResult;

typedef enum {
  EXECUTE_SUCCESS,
  EXECUTE_TABLE_FULL,
} ExecuteResult;

int handle_prepare_result(PrepareResult result, InputBuffer *input_buffer);

#endif
