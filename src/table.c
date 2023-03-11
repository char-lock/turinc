#include "../include/turinc_table.h"

Table* table_alloc(void) {
  Table* table = malloc(sizeof(Table));
  // printf("table_alloc -> table alloc'd\n");
  table->row_count = 0;
  table->state_count = 0;
  table->symbol_count = 0;
  table->states = malloc(8);
  table->symbols = malloc(8);
  table->rows = malloc(sizeof(TableRow) * 8);
  // printf("table_alloc -> zero'd\n");
  table_add_state(table, 0);
  // printf("table_alloc -> state added\n");
  table_add_symbol(table, 0);
  // printf("table alloc -> symbol added\n");
  return table;
}

void table_free(Table* table) {
  free(table->symbols);
  free(table->states);
  for (size_t r = 0; r < table->row_count; r++) {
    free(table->rows[r]);
  }
  free(table->rows);
  free(table);
}

TableRow* table_row_alloc(
  unsigned char c_state, unsigned char r_sym,
  unsigned char w_sym, int m_dir, unsigned char n_state
) {
  TableRow* row = malloc(sizeof(TableRow));
  row->current_state = c_state;
  row->read_symbol = r_sym;
  row->write_symbol = w_sym;
  row->move_direction = m_dir;
  row->next_state = n_state;
  return row;
}

void table_add_row(Table *table, TableRow *row) {
  TableRow **rows = realloc(table->rows, sizeof(TableRow*) * (table->row_count + 1));
  table->rows = rows;
  table->rows[table->row_count] = row;
  table->row_count++;
}

void table_add_symbol(Table *table, unsigned char symbol) { 
  table->symbols = realloc(table->symbols, table->symbol_count + 1);
  table->symbols[table->symbol_count] = symbol;
  table->symbol_count++;
}

void table_add_state(Table *table, unsigned char state) {
  table->states = realloc(table->states, table->state_count + 1);
  // printf("table_add_state -> realloc'd\n");
  table->states[table->state_count] = state;
  table->state_count++;
}

int table_symbol_valid(Table *table, unsigned char symbol) {
  int valid = 0;
  for (size_t s = 0; s < table->symbol_count; s++) {
    if (table->symbols[s] == symbol) {
      valid = 1;
      break;
    }
  }
  return valid;
}

int table_state_valid(Table *table, unsigned char state) {
  int valid = 0;
  for (size_t s = 0; s < table->state_count; s++) {
    if (table->states[s] == state) {
      valid = 1;
      break;
    }
  }
  return valid;
}

TableRow* table_get_row(Table *table, unsigned char sym, unsigned char state) {
  for (size_t r = 0; r < table->row_count; r++) {
    if (table->rows[r]->current_state == state) {
      if (table->rows[r]->read_symbol == sym) {
        return table->rows[r];
      }
    }
  }
  printf("error: unable to locate requested state and symbol row");
  exit(-1);
}
