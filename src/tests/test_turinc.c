#include "../../include/turinc.h"

int main(void) {
  // Testing by implementing the Busy Beaver turing machine.
  TurincContext *ctx = turinc_ctx_alloc();

  // printf("Ctx alloc'd.\n");

  table_add_symbol(ctx->sym_state_table, 1);
  // printf("Symbols added.\n");
  for (unsigned char s = 1; s < 4; s++) {
    table_add_state(ctx->sym_state_table, s);
  }
  // printf("States added.\n");
  ctx->current_state = 1;
  ctx->halt_state = 0;
  ctx->head_pos = 0;
  // printf("Initial state set.\n");



  TableRow *r_sy0_st1 = table_row_alloc(1, 0, 1, 1, 2);
  TableRow *r_sy1_st1 = table_row_alloc(1, 1, 1, -1, 3);
  TableRow *r_sy0_st2 = table_row_alloc(2, 0, 1, -1, 1);
  TableRow *r_sy1_st2 = table_row_alloc(2, 1, 1, 1, 2);
  TableRow *r_sy0_st3 = table_row_alloc(3, 0, 1, -1, 2);
  TableRow *r_sy1_st3 = table_row_alloc(3, 1, 1, 1, 0);

  // printf("Rows alloc'd.\n");

  table_add_row(ctx->sym_state_table, r_sy0_st1);
  table_add_row(ctx->sym_state_table, r_sy1_st1);
  table_add_row(ctx->sym_state_table, r_sy0_st2);
  table_add_row(ctx->sym_state_table, r_sy1_st2);
  table_add_row(ctx->sym_state_table, r_sy0_st3);
  table_add_row(ctx->sym_state_table, r_sy1_st3);

  // printf("Rows added.\n");

  turinc_ctx_start(ctx);

  return 0;
}