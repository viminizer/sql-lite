#include "headers/result.h"
#include <stdio.h>

int handle_prepare_result(PrepareResult result, InputBuffer *input_buffer) {
  switch (result) {
  case PREPARE_SUCCESS:
    return 1; // OK, continue

  case PREPARE_SYNTAX_ERROR:
    printf("Syntax error. Could not parse statement.\n");
    return 0;

  case PREPARE_STRING_TOO_LONG:
    printf("String is too long.\n");
    return 0;

  case PREPARE_NEGATIVE_ID:
    printf("ID must be positive.\n");
    return 0;

  case PREPARE_UNRECOGNIZED_STATEMENT:
    printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
    return 0;
  }
  return 0; // Fallback
}
