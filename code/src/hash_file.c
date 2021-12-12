
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int * file;          ///////////// auto ?????
#include "bf.h"
#include "hash_file.h"
#define MAX_OPEN_FILES 20

#define CALL_BF(call)       \
{                           \
  BF_ErrorCode code = call; \
  if (code != BF_OK) {         \
    BF_PrintError(code);    \
    return BF_ERROR;        \
  }                         \
}                            \

typedef struct node{
  Record r;
  struct node * next;
  int depth;
} bucket;
typedef struct node1{
  bucket * b;
  int id;
  struct node1* next;
} directory;       
void push(bucket * head, Record r,int d);
Record pop(bucket ** head);
Record remove_last(bucket * head);
Record remove_by_index(bucket ** head, int n);
void pushd(directory * head, bucket * b,int i);
///////////////directory dir;
FILE * fp=NULL; 
HT_ErrorCode HT_Init() {
  file=malloc(MAX_OPEN_FILES*sizeof(int)); ////na arxikopoihsw ton pinaka me ta files edw o pinakas twra exei mono pointers se files 
//g  FILE files[MAX_OPEN_FILES]; 
  
  return HT_OK;
}

HT_ErrorCode HT_CreateIndex(const char *filename, int depth) {
  directory dir; 
  printf("Created empty directory.\n");                 ///////dhmioyrgia directory mesa sthn create index kai oxi global 
  int i;
  BF_Block *block;
  BF_Block_Init(&block); 
  for(i=0;i<depth*2;i++){ 
    //BF_AllocateBlock()      //dhmiourgw directory me 4 kelia afou global depth=2 me pointers NULL afou buckets adeia
    pushd(&dir,NULL,i);
  }
  BF_CreateFile(filename); 
  
  
  return HT_OK;
}

HT_ErrorCode HT_OpenIndex(const char *fileName, int *indexDesc){
  
  //BF_CreateFile(fileName); 
}

HT_ErrorCode HT_CloseFile(int indexDesc) {        //otan ena file kleinei prepei na vgainei kai apo ton pinaka me ta files kai na apodesmeyetai o xwros toy
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
void push(bucket * head, Record r,int d) {
    bucket * current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    /* now we can add a new variable */
    current->next = (bucket *) malloc(sizeof(bucket));
    current->next->r = r;
    current->next->depth=d;
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

