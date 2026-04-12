#include <stdio.h>
#include <stdlib.h>

__attribute__((noinline))
void MAYALIAS(void* p, void* q){
  printf("\n");
}

__attribute__((noinline))
void NOALIAS(void* p, void* q){
  printf("\n");
}
