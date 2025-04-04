#include "queue.h"
#include "tile_game.h"
#include "linked_list.h"
#include <stdio.h>

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
  struct queue q = {list};
  enqueue(&q, start);

  //just copy paste the search from the README
  //for children, use the posible moves
  //check to make sure we dont make a move such that the new game state=old game state
  //also check for invalid moves
  while (q.data.head != NULL){
    fprintf(stderr, "did thing\n");
    struct game_state currState = dequeue(&q);
    if (serialize(currState) == serialize(solved)){     //if currState is solved,
      return currState.num_steps;
    }
    else{
      fprintf(stderr, "afokoawd\n");
      if (currState.empty_col < 3){     //move right if we can
        struct game_state childState = start;
        move_right(&childState);
        enqueue(&q, childState);
      }
      if (currState.empty_col > 0){     //move left if we can
        struct game_state childState = start;
        move_left(&childState);
        enqueue(&q, childState);
      }if (currState.empty_row > 0){
        struct game_state childState = start;
        move_up(&childState);
        enqueue(&q, childState);
      }
      if (currState.empty_row < 3){
        struct game_state childState = start;
        move_down(&childState);
        enqueue(&q, childState);
      }
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
