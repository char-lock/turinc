#ifndef __TURINC__H__
#define __TURINC__H__

#include "./turinc_includes.h"
#include "./turinc_table.h"
#include "./turinc_tape.h"

typedef struct {
  Tape *tape;
  size_t head_pos;
  Table *sym_state_table;
  unsigned char current_state;
  unsigned char halt_state;
} TurincContext;
TurincContext* turinc_ctx_alloc(void);
void turinc_ctx_move(TurincContext *ctx, int dir);
unsigned char turinc_ctx_read(TurincContext *ctx);
void turinc_ctx_write(TurincContext *ctx, unsigned char sym);
void turinc_ctx_operation(TurincContext *ctx);
void turinc_ctx_free(TurincContext *ctx);
void turinc_ctx_print(TurincContext *ctx);
void turinc_ctx_start(TurincContext *ctx);

#endif // __TURINC__H__