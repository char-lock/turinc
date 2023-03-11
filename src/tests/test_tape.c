#include "../../include/turinc_tape.h"

int main(void) {
  Tape *tape = tape_alloc();
  printf("Length: %i; Starting Position: %i\n", tape->length, tape->start_pos);
  tape_extend_right(tape, 2);
  printf("Length: %i; Starting Position: %i\n", tape->length, tape->start_pos);
  tape_extend_left(tape, 2);
  printf("Length: %i; Starting Position: %i\n", tape->length, tape->start_pos);
  tape_free(tape);
  return 0;
}