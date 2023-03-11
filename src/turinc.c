#include "../include/turinc.h"

TurincContext* turinc_ctx_alloc(void) {
  TurincContext *ctx = malloc(sizeof(TurincContext) * 10);
  // printf("turinc_ctx_alloc -> ctx alloc'd\n");
  ctx->current_state = 0;
  ctx->halt_state = 0;
  ctx->head_pos = 0;
  // printf("turinc_ctx_alloc -> state set\n");
  ctx->sym_state_table = table_alloc();
  // printf("turinc_ctx_alloc -> table alloc'd\n");
  ctx->tape = tape_alloc();
  // printf("turinc_ctx_alloc -> tape alloc'd\n");
  return ctx;
}

void turinc_ctx_move(TurincContext *ctx, int dir) {
  if (ctx->head_pos == 0 && dir < 0) {
    tape_extend_left(ctx->tape, 8 + (dir * -1) - 1);
    ctx->head_pos += 8 + (dir * -1) - 1;
  } else if (ctx->head_pos == (ctx->tape->length - 1) && dir > 0) {
    tape_extend_right(ctx->tape, 8 + dir - 1);
  }
  ctx->head_pos += dir;
}

unsigned char turinc_ctx_read(TurincContext *ctx) {
  // printf("turinc_ctx_read -> inside\n");
  return tape_read(ctx->tape, ctx->head_pos);
}

void turinc_ctx_write(TurincContext *ctx, unsigned char sym) {
  if (!table_symbol_valid(ctx->sym_state_table, sym)) {
    printf("error: invalid symbol provided\n");
    exit(-1);
  }
  ctx->tape->values[ctx->head_pos] = sym;
}

void turinc_ctx_operation(TurincContext *ctx) {
  unsigned char sym = turinc_ctx_read(ctx);
  // printf("turinc_ctx_operation -> read symbol '%i'\n", sym);
  unsigned char state = ctx->current_state;
  // printf("turinc_ctx_operation -> got state '%i'\n", state);
  if (state == ctx->halt_state) return;
  TableRow *res = table_get_row(ctx->sym_state_table, sym, state);
  // printf("turinc_ctx_operation -> got row for sym %i, st %i\n", res->read_symbol, res->current_state);
  turinc_ctx_write(ctx, res->write_symbol);
  turinc_ctx_move(ctx, res->move_direction);
  ctx->current_state = res->next_state;
  turinc_ctx_print(ctx);
}

void turinc_ctx_print(TurincContext *ctx) {
  // printf("TURINC STATE:\nHead Position -> %i\n", ctx->head_pos);
  size_t start = ctx->head_pos >= 5 ? ctx->head_pos - 5 : 0;
  size_t end = ctx->tape->length >= ctx->head_pos + 5 ? ctx->head_pos + 5 : ctx->tape->length;
  if (end - start < 10) {
    for (size_t i = 0; i < (10 - (end - start)); i++) {
      printf("0 ");
    }
  }
  for (size_t p = start; p < end; p++) {
    printf("%i ", ctx->tape->values[p]);
  }
  printf("\n");
  if (end - start < 10) {
    for (size_t i = 0; i < (10 - (end - start)); i++) {
      printf("  ");
    }
  }
  for (size_t p = start; p < end; p++) {
    if (p == ctx->head_pos) {
      printf("^ ");
    } else {
      printf("  ");
    }
  }
  printf("\nSTATE: %i | HEAD: %i", ctx->current_state, ctx->head_pos);
  printf("\n\n\n");
}

void turinc_ctx_free(TurincContext *ctx) {
  tape_free(ctx->tape);
  table_free(ctx->sym_state_table);
  free(ctx);
}

void turinc_ctx_start(TurincContext *ctx) {
  while (ctx->current_state != ctx->halt_state) {
    turinc_ctx_operation(ctx);
  }
}