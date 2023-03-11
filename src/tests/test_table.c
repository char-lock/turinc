#include "../../include/turinc_table.h"

int main(void) {
  Table* table = table_alloc();
  printf("================================\n");
  printf(" TEST #0 -- Table & Table Rows\n");
  printf("================================\n");
  printf("Symbols: %i; States: %i; Rows: %i\n", table->symbol_count, table->state_count, table->row_count);
  TableRow* row = table_row_alloc(1, 0, 1, 1, 2);
  printf(
    "St.%i Sym.%i -> Sym.%i Mov.%i St.%i\n\n",
    row->current_state, row->read_symbol,
    row->write_symbol, row->move_direction, row->next_state
  );
  table_add_row(table, row);
  printf("Symbols: %i; States: %i; Rows: %i\n", table->symbol_count, table->state_count, table->row_count);
  printf(
    "St.%i Sym.%i -> Sym.%i Mov.%i St.%i\n",
    table->rows[0]->current_state, table->rows[0]->read_symbol,
    table->rows[0]->write_symbol, table->rows[0]->move_direction, table->rows[0]->next_state
  );
  printf("\n\n");
  printf("================================\n");
  printf(" TEST #1 -- Symbols & States\n");
  printf("================================\n");
  printf("Symbols: %i; States: %i; Rows: %i\n", table->symbol_count, table->state_count, table->row_count);
  printf("Sym[0]: %i; St[0]: %i\n\n", table->symbols[0], table->states[0]);
  table_add_state(table, 2);
  table_add_symbol(table, 1);
  printf("Symbols: %i; States: %i; Rows: %i\n", table->symbol_count, table->state_count, table->row_count);
  printf("Sym[1]: %i; St[1]: %i\n", table->symbols[1], table->states[1]);
  // table_add_row(table, row);
  // printf("Rows: %i\n", table->row_count);
  free(row);
  table_free(table);
  return 0;
}
