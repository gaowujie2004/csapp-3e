#include <stdio.h>

union ele
{
    struct
    {
        long *p;
        long y;
    } e1;

    struct
    {
        long x;
        union ele *next;
    } e2;
};

void proc2(union ele *up)
{
    printf("proc2  up->e2.next =  %p\n", up->e2.next);
    printf("proc2  up->e2.next->e2.x =  %d", up->e2.next->e2.x);

}

void main()
{
    union ele e0;
    e0.e2.x = 100;
    e0.e2.next = NULL;

    union ele e1;
    e1.e2.x = 200;
    e1.e2.next = &e0;
    printf("main e0 address = %p \n", &e0);
    proc2(&e1);
}