#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
  struct list_node * n = malloc(sizeof(struct list_node));    //create node of size list_node
  n -> value = value;   //set node.val to value
  n -> next = NULL;       //set node.next to nothing (create a singluar node);
  return n;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node * newNode = new_node(value);     //create new independent node with value
  newNode -> next = list -> head;     //set newNode.next to previous list such that independent node is the new head
  list -> head = newNode;   //set list to newNode
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node * newNode = new_node(value);   //create new node

  if (list -> head == NULL) list -> head = newNode;

  struct list_node * currNode = list -> head;   //set current node to start of list
  while ((currNode -> next) != NULL){   //loop to find last value of node
    currNode = currNode -> next;    
  }
  currNode -> next = newNode;   //set next of final node to newNode
}

size_t remove_from_head(struct linked_list *list) {
  size_t returnVal = list -> head -> value;   //get value of head
  struct list_node* newList = list -> head -> next;     //set newList to next node after head
  free (list);
  list -> head = newList;
  return returnVal;
}

size_t remove_from_tail(struct linked_list *list) {
  struct list_node * currNode = list -> head;
  struct list_node *nextNode = currNode -> next;
  size_t returnVal;

  if (nextNode == NULL){      //if only 1 val in list, nextNode is null
    fprintf(stderr, "emptr\n");
    returnVal = currNode -> value;
    free(currNode);   //thus get head's value and return and remove
    return returnVal;
  }

  while (currNode -> next != NULL){
    fprintf(stderr, "doing thignsg\n");
    currNode = currNode -> next;    //find last node
    nextNode = nextNode -> next;    //nextNode = last node, currNode = nextNode -1
  }
  returnVal = nextNode -> value;
  currNode -> next = NULL;
  free(nextNode);
  return returnVal;
}

void free_list(struct linked_list list) {
  struct list_node *currNode = list.head;
  while(currNode != NULL){
    struct list_node *nextNode = currNode -> next;
    free(currNode);
    currNode = nextNode;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
