#include "aliascheck.h"

int main(){

  int **a, *b, *x ,c;
  c = 10;
  a = &b;
  b = &c;
  x = *a;
  int y = *x;
  MAYALIAS(x,&c);
  MAYALIAS(x,b);
  return 0;
}
