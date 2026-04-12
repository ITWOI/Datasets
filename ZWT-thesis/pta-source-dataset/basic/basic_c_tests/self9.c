// 比较normalize和register，前者将Store转换为INT_ADD，后者会保留Store
#include "aliascheck.h"

int main()
{
	int **q, **p;
	int a,b;

    int* p_arr[2];
    p_arr[0] = &a;
    p_arr[1] = &b;

	q = &p_arr[0];

	p = q+b;    // 如果b是1，则别名成立
	MAYALIAS(*p,&b);
	return 0;
}
