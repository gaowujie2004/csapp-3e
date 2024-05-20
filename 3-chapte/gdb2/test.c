#include <stdio.h>

extern void fn1();

int main()
{
    fn1();
    long a1 = 10;
    __int64 a2 = -1;
    __int64 a3 = -10;
    __int64 a4 = 0x1234567890abcdef;
    printf("第一次");
    printf("第二次");
    printf("\n&a2 --> %p \n", &a2);
    printf("\n&a4 --> %p \n", &a4);

    return 0;
}
