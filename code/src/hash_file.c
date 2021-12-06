#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bf.h"
#include "hash_file.h"
#define MAX_OPEN_FILES 20

#define CALL_BF(call)       \
{                           \
  BF_ErrorCode code = call; \
  if (code != BF_OK) {         \
    BF_PrintError(code);    \
    return HP_ERROR;        \
  }                         \
}                            \
int *file=malloc(MAX_OPEN_FILES*sizeof(int));
typedef struct node{
  Record r;
  struct node * next;
} bucket;
typedef struct node1{
  bucket * b;
  int id;
  struct node1* next;
} directory;       
void push(bucket * head, Record r);
Record pop(bucket ** head);
Record remove_last(bucket * head);
Record remove_by_index(bucket ** head, int n);
void pushd(directory * head, bucket * b,int i);
struct node * popd(directory ** head);
struct node * remove_lastd(directory * head);
HT_ErrorCode HT_Init() {
  directory dir;

  return HT_OK;
}

HT_ErrorCode HT_CreateIndex(const char *filename, int depth) {


  HT_Init();
  int i;
  for(i=0;i<(depth*2);i++){
    pushd(dir,NULL,i);
  }
  return HT_OK;
}

HT_ErrorCode HT_OpenIndex(const char *fileName, int *indexDesc){
  //insert code here
  return HT_OK;
}

HT_ErrorCode HT_CloseFile(int indexDesc) {
  //insert code here
  return HT_OK;
}

HT_ErrorCode HT_InsertEntry(int indexDesc, Record record) {
  //insert code here
  return HT_OK;
}

HT_ErrorCode HT_PrintAllEntries(int indexDesc, int *id) {
  //insert code here
  return HT_OK;
}
void push(bucket * head, Record r) {
    bucket * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    /* now we can add a new variable */
    current->next = (bucket *) malloc(sizeof(bucket));
    current->next->r = r;
    current->next->next = NULL;
  }
  Record pop(bucket ** head) {
    Record retval;
    bucket * next_node = NULL;

    if (*head == NULL) {
        printf("poping from empty list");
    }

    next_node = (*head)->next;
    retval = (*head)->r;
    free(*head);
    *head = next_node;

    return retval;
  }
  Record remove_last(bucket * head) {
    Record retval;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        retval = head->r;
        free(head);
        return retval;
    }

    /* get to the second to last node in the list */
    bucket * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    retval = current->next->r;
    free(current->next);
    current->next = NULL;
    return retval;

  }
  Record remove_by_index(bucket ** head, int n) {
    int i = 0;
    Record retval;
    bucket * current = *head;
    bucket * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            printf("cant pop");
        }
        current = current->next;
    }

    if (current->next == NULL) {
        printf("cant pop");
    }

    temp_node = current->next;
    retval = temp_node->r;
    current->next = temp_node->next;
    free(temp_node);

    return retval;
  }
  //////////////////////////// directories









  void pushd(directory * head, bucket * b,int i) {
    directory * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (directory *) malloc(sizeof(directory));
    current->next->b = b;
    current->next->id=i;
    current->next->next = NULL;
  }
  struct node * popd(directory ** head) {
    struct node  *retval ;
    directory * next_node = NULL;

    if (*head == NULL) {
        printf("poping from empty list");
    }

    next_node = (*head)->next;
    retval = (*head)->b;
    free(*head);
    *head = next_node;

    return retval;
  }
  struct node * remove_lastd(directory * head) {
    struct node *retval;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        retval = head->b;
        free(head);
        return retval;
    }

    /* get to the second to last node in the list */
    directory * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    retval = current->next->b;
    free(current->next);
    current->next = NULL;
    return retval;

  }
