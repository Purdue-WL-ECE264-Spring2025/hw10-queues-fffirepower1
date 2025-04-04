#include "queue.h"
#include "tile_game.h"
#include "linked_list.h"
#include <stdio.h>

void printTable(struct game_state state){
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      fprintf(stderr, "%d ", state.tiles[i][j]);
    }
    fprintf(stderr,"\n");
  }
  fprintf(stderr, "\n");
}

void enqueue(struct queue *q, struct game_state state) {
  size_t currNode = serialize(state);         //get current game state
  insert_at_head(&(q -> data), currNode);     //insert current game state to start of queue
}

struct game_state dequeue(struct queue *q) { 
  size_t nodeData = remove_from_tail(&(q -> data));
  return deserialize(nodeData);
}

int number_of_moves(struct game_state start) {
  struct linked_list list = {NULL};
  struct game_state solved = {{{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}}, 4, 4, 0};
  fprintf(stderr, "%ld\n", serialize(solved));
  struct game_state prevState = start;
  struct queue q = {list};
  struct queue prevQ = {list};      //queue for previous states
  enqueue(&q, start);
  enqueue(&prevQ, start);     //add starting state to prevQ
  int num = 0;
  int num2 = 0;

  //just copy paste the search from the README
  //for children, use the posible moves
  //check to make sure we dont make a move such that the new game state=old game state
  //also check for invalid moves
  while (num2 < 20){
    struct game_state currState = dequeue(&q);
    //fprintf(stderr, "num children: %ld\n", num);
    fprintf(stderr, "numSteps: %d   empty spot %d %d   data %ld\n", currState.num_steps, currState.empty_col, currState.empty_row, serialize(currState));
    if (serialize(currState) == serialize(solved)){     //if currState is solved,
      return currState.num_steps;
    }
    else{
      if (num == 0)prevState = dequeue(&prevQ);      //get most parent state
      fprintf(stderr, "PREV STATE: \n");
      printTable(prevState);
      struct game_state childState = currState;
      fprintf(stderr, "%d, %d\n", childState.empty_col, childState.empty_row);
      if ((serialize(childState) != serialize(prevState)) && childState.empty_col < 3) {move_left(&childState); enqueue(&q, childState); num++;}
      printTable(childState);
      childState = currState;     //reset child state
      if (serialize(childState) != serialize(prevState) && childState.empty_col > 0) {move_right(&childState);enqueue(&q, childState); num++;}
      printTable(childState);
      childState = currState;
      move_up(&childState);
      if (serialize(childState) != serialize(prevState) && childState.empty_row < 3) {enqueue(&q, childState); num++;}
      printTable(childState);
      childState = currState;
      move_down(&childState);
      if (serialize(childState) != serialize(prevState) && childState.empty_row > 0) {enqueue(&q, childState); num++;}
      printTable(childState);
        
      dump_list(q.data);
      enqueue(&prevQ, currState);      //after adding children, set prevstate the current testing state
      num--;
      num2++;
      //on next run through, currState is updated while prevState remains old currState
    }
  }
  /*node bfs(graph g, node start, node search) {
    queue q = new_queue();
    while (!empty(s)) {
        node cur = dequeue(&q);
        if (equals(cur, search)) {
            return cur;
        } else {
            for (node child in children(cur)) {
                enqueue(&q, child);
            }
        }
    }*/
   return 0;
}
