#include "../include/turinc_tape.h"

Tape* tape_alloc(void) {
  Tape* tape = malloc(sizeof(Tape));
  tape->start_pos = 0;
  tape->length = 8;
  tape->values = malloc(8);
  for (size_t p = 0; p < 8; p++) {
    tape->values[p] = 0;
  }
  return tape;
}

void tape_extend_right(Tape *tape, size_t amount) {
  tape->values = realloc(tape->values, tape->length + amount);
  for (size_t p = tape->length; p < tape->length + amount; p++) {
    tape->values[p] = 0;
  }
  tape->length += amount;
}

void tape_extend_left(Tape *tape, size_t amount) {
  tape->values = realloc(tape->values, tape->length + amount);
  for (size_t p = 0; p < tape->length; p++) {
    tape->values[p + amount] = tape->values[p];
    tape->values[p] = 0;
  }
  tape->length += amount;
  tape->start_pos += amount;
}

unsigned char tape_read(Tape *tape, size_t pos) {
  if (pos < 0 || pos >= tape->length) {
    return 0;
  }
  return tape->values[pos];
}

void tape_free(Tape *tape) {
  free(tape->values);
  free(tape);
}
