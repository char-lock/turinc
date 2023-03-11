#ifndef __TURINC__TABLE__H__
#define __TURINC__TABLE__H__

#include "./turinc_includes.h"

typedef struct {
  unsigned char read_symbol;
  unsigned char current_state;
  unsigned char write_symbol;
  int move_direction;
  unsigned char next_state;
} TableRow;
TableRow* table_row_alloc(unsigned char c_state, unsigned char r_sym, unsigned char w_sym, int m_dir, unsigned char n_state);
// Just use `free` for a TableRow.

typedef struct {
  unsigned char *symbols;
  size_t symbol_count;
  unsigned char *states;
  size_t state_count;
  TableRow** rows;
  size_t row_count;
} Table;
Table* table_alloc(void);
void table_add_row(Table *table, TableRow *row);
void table_add_symbol(Table *table, unsigned char symbol);
void table_add_state(Table *table, unsigned char state);
int table_symbol_valid(Table *table, unsigned char symbol);
int table_state_valid(Table *table, unsigned char state);
TableRow* table_get_row(Table *table, unsigned char sym, unsigned char state);
void table_free(Table* table);

#endif // __TURINC__TABLE__H__