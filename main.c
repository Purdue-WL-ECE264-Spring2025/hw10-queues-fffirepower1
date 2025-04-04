#include "queue.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [test file]\n", argv[0]);
    exit(1);
  }

  FILE *fp = fopen(argv[1], "r");
  if (!fp) {
    fprintf(stderr, "Failed to open input file %s\n", argv[1]);
    exit(2);
  }

  int expected;
  fscanf(fp, "%d", &expected);

  struct game_state start;
  start.num_steps = 0;
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      int value;
      fscanf(fp, "%d", &value);
      start.tiles[i][j] = value;
      if (value == 0) {
        start.empty_row = i;
        start.empty_col = j;
        //fprintf(stderr, "%d %d\n", (int)i, (int)j);
      }
    }
  }
  serialize(start);
  fclose(fp);

  /* queue q = {};
  enqueue(&q, start);
  dump_list(q.data);
  fprintf(stderr, "%ld\n", serialize(dequeue(&q)));
  enqueue(&q, start);
  dump_list(q.data);
  dequeue(&q);*/
  int output = number_of_moves(start);
  if (output != expected) {
    fprintf(stderr, "Expected %d moves, got %d\n", expected, output);
    exit(3);
  }

  return 0;
}
