
#include <stdio.h>
#include <stdlib.h>
int * file; 
#include <string.h>
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


typedef struct node1{
  BF_Block * b; 
  int id;
  struct node1* next;
} directory;       

void pushd(directory * head, BF_Block * b,int i);



HT_ErrorCode HT_Init() {
  file = malloc(MAX_OPEN_FILES*sizeof(int*)); 

  return HT_OK;
}

HT_ErrorCode HT_CreateIndex(const char *filename, int depth) {
  directory dir; 
  printf("Created empty directory.\n");                 ///////dhmioyrgia directory mesa sthn create index kai oxi global 
  int i;
  int fp=1; 
 
  for(i=0;i<depth*2;i++){ 
    BF_Block * block; 
    BF_AllocateBlock(fp,block);      //dhmiourgw directory me 4 kelia afou global depth=2 me pointers NULL afou BF_Blocks adeia
    pushd(&dir,block,i); 
  }
  BF_CreateFile(filename);
  int * blocksnum;  
  BF_GetBlockCounter(fp,blocksnum);
  printf("blocks num %d\n", blocksnum); 
  
  
  return HT_OK;
}

HT_ErrorCode HT_OpenIndex(const char *fileName, int *indexDesc){
  
  //Bf_openfile(fileName); 
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

  //////////////////////////// directories


  void pushd(directory * head, BF_Block * b,int i) {
    directory * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // now we can add a new variable 
    current->next = (directory *) malloc(sizeof(directory));
    current->next->b = b;
    current->next->id=i;
    current->next->next = NULL;
  }
   