#include "meta_command.h"
#include "result.h"
#include "statement.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_ssize_t.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Must supply a database filename.\n");
    exit(EXIT_FAILURE);
  }
  char *filename = argv[1];
  Table *table = db_open(filename);
  InputBuffer *input_buffer = new_input_buffer();
  while (1) {
    print_prompt();
    read_input(input_buffer);

    if (input_buffer->buffer[0] == '.') {
      switch (do_meta_command(input_buffer, table)) {
      case (META_COMMAND_SUCCESS):
        continue;
      case (META_COMMAND_UNRECOGNIZED_COMMAND):
        printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        continue;
      }
    }

    Statement statement;
    handle_prepare_result(prepare_statement(input_buffer, &statement),
                          input_buffer);

    switch (execute_statement(&statement, table)) {
    case (EXECUTE_SUCCESS):
      printf("Executed.\n");
      break;
    case (EXECUTE_DUPLICATE_KEY):
      printf("Duplicate key error.\n");
      break;
    case (EXECUTE_TABLE_FULL):
      printf("Error.Table full\n");
      break;
    }
  }
}
