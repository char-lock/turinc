#ifndef __TURINC__TAPE__H__
#define __TURINC__TAPE__H__

#include "./turinc_includes.h"

typedef struct {
  unsigned char *values;
  size_t length;
  size_t start_pos;
} Tape;
Tape* tape_alloc(void);
void tape_extend_right(Tape *tape, size_t amount);
void tape_extend_left(Tape *tape, size_t amount);
unsigned char tape_read(Tape *tape, size_t pos);
void tape_free(Tape *tape);

#endif // __TURINC__TAPE__H__