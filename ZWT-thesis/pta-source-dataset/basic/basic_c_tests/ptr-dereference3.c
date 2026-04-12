#include "aliascheck.h"
void foo(int q){
  int i = 10;
  int k = i;

}
int main(){

int *s,*r,*x,**y,t,z,k;
	s = &t;
	r = &z;
	y = &r;
	s = r;
  MAYALIAS(s,&z);
	x = *y;
  MAYALIAS(x,r);
	foo(k);
return 0;
}
