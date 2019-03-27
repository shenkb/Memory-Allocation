#include <stdio.h>
#include <stdlib.h>
#include "memorymgr.h"

int* first = NULL;
int* last = NULL;

void  initmemory(int size);  // initialize a simulated heap
void *myalloc(int length);   // allocate a block of length (or more) bytes
void  myfree(void *ptr);     // free an allocated block
void  coalesce();            // go through the heap, coalescing unallocated blocks
void  printallocation();  // print info about the simulated heap, for debugging purposes

int  isAllocated(int *p);  // is the block at location p allocated?
int *nextBlock(int *p);    // return a pointer to the block that follows p
int *firstBlock();         // return a pointer to the first block on the heap
int *lastBlock();          // return a pointer to the sentinel block

int multi8 (int a);        // return the closest multiple of 8

void initmemory (int size) {
  int a = multi8( size + 12 );
  first = (int*) malloc (a * sizeof(int));
  last = first + a;
  *last = 0;
  first = first + 1;
  *first = a - 8;
}

void* myalloc (int length) {
  int* p = firstBlock ();
  int memor = multi8(length + 4);
  while ( p < lastBlock () ) {
    if (isAllocated(p) == 1) { // allocated
      p = nextBlock(p);
    } else { // find an unallocated space
      if (*p == memor) {
        *p = memor + 1;
        p = p + 1;
        break;
      }
      if (*p > memor) {
        int temp = *p;
        *p = memor + 1; //allocated
        int* q = nextBlock(p);
        *q = temp - memor; //unallocated
        p = p + 1;
        break;
      }
      else {
        p = nextBlock(p);
        if (*p == 0) { p = NULL; break;} // no space
      }
    }
  }
  return p; //已加一
}

void myfree (void* ptr) {
  ptr = (int *) ptr - 1;
  *((int *)ptr) = *((int *)ptr) & (-2);
}

void coalesce() {

  int* temp = firstBlock();

  while ( *nextBlock(temp) != 0 ) {
    if (isAllocated(temp) == 0 && isAllocated(nextBlock(temp)) == 0) {
      *temp = *temp + *nextBlock(temp);
    }
    else { temp = nextBlock(temp); }
    }

}

//if (isAllocated(temp) == 1) { // allocated
//  temp = nextBlock(temp);
//} else {
//  int* temp2 = nextBlock(temp);
//  if (isAllocated(temp2) == 0) {
//    *temp = *temp + *temp2;
//  } else {
//    temp = nextBlock(temp);
//  }

void printallocation () {
  //if (p = NULL) {printf()}
  int* temp = firstBlock();
  int i = 0;
  while ( *temp != 0 ) {
    if (isAllocated(temp) == 1) {
      printf("Blook %d: size %d   allocated\n", i, *temp -1 );
    } else {
      printf("Blook %d: size %d   unallocated\n", i, *temp );
    }
    i ++;
    temp = nextBlock(temp);
  }
}

int* firstBlock () { return first; }
int* lastBlock () { return last; }
int isAllocated(int* p) { return *p % 2; } //hexa divi
int* nextBlock(int* p) { return p + (*p / 4); }

int multi8 (int a) {
  if (a % 8 == 0) { return a; }
  else { return ((a/8)+1)*8; }
}


// int main (int argc, char *argv[]) {
//  int *p1, *p2;

//  printf("initial allocation\n");
//  initmemory(56);
//  printallocation();

//  p1 = (int *) myalloc(20);
//  printf("myalloc(20)\n");
//  printallocation ();

//  p2 = (int *) myalloc(10);
//  printf("myalloc(10)\n");
//  printallocation ();

//  myfree(p1); p1 = NULL;
//  printf("free (malloc 20)\n");
//  printallocation ();

//  p1 = (int *)myalloc(4);
//  printf("malloc 4\n");
//  printallocation();

//  printf("free (malloc 10)\n");
//  myfree(p2); p2 = NULL;
//  printallocation();

//  printf("malloc 30: should fail\n");
//  p2 = (int *)myalloc(30);
//  if (p2 == NULL) {printf("allocation failed.\n");}

//  printf("coalesce\n");


//  coalesce();
//  printallocation();

//  printf("malloc 30 \n");  // now this succeeds
//  p2 = (int *) myalloc(30);
//  printallocation();



//  printf("free everything\n");
//  myfree(p1); p1 = NULL;
//  myfree(p2); p2 = NULL;
//  printallocation();

//  printf("malloc 56: should fail\n");
//  // this will fail
//  p1 = (int *)myalloc(56);
//  if (p1 == NULL) {printf("allocation failed.\n");}

//  printf("coalesce\n");
//  coalesce();
//  printallocation();

//  printf("malloc 56\n");
//  p1 = (int *)myalloc(56);
//  printallocation();


//   return 0;
// }
