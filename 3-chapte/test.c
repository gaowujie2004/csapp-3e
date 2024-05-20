#include <stdio.h>
#include <string.h>
#include <immintrin.h>

// char *gets(char *s)
// {
//     int c;
//     char *dest = s;

//     while ((c = getchar()) != '\n' && c != EOF)
//     {
//         printf("in while %d\n", c);
//         *dest++ = c;
//     }

//     if (c == EOF && dest == s)
//     {
//         /* No characters read */
//         return NULL;
//     }

//     printf("\n\ndao zhe li %d", c);
//     *dest++ = '\0'; /* Terminate string */

//     return s;
// }

// /* Read input line and write it back */
// void echo()
// {
//     char buf[8]; /*Way too small! */
//     gets(buf);
//     puts(buf);
// }

// void test_getchar()
// {
//     char a;
//     char b;
//     char c;

//     printf("1-input: \n");
//     a = getchar();

//     printf("2-input: \n");
//     b = getchar();

//     c = getchar();
//     printf("3-input: \n");

//     printf("\n\nis: %u %u %u", a, b, c);
// }



// int len(char *s)
// {
//     return strlen(s);
// }

// void iptoa(char *s, long *p)
// {
//     long val = *p;
//     sprintf(s, "?", val);
// }

// int intlen(long x)
// {
//     long v;
//     char buf[12];
//     v = x;
//     iptoa(buf, &v);
//     return len(buf);
// }

void store_prod(__int128_t *dest, __int64 x, __int64 y) {
 *dest = x * y;
}




int main() {
    // // 创建两个128位寄存器，每个寄存器包含四个单精度浮点数
    // __m128 a = _mm_set_ps(4.0, 3.0, 2.0, 1.0);
    // __m128 b = _mm_set_ps(8.0, 7.0, 6.0, 5.0);

    // // 执行单精度浮点数的标量加法操作
    // __m128 result = _mm_add_ss(a, b);

    // // 打印结果
    // float* res = (float*)&result;
    // printf("Result: %f\n", res[0]); // 打印结果寄存器中的第一个单精度浮点数
    // printf("Result: %f\n", res[1]); // 打印结果寄存器中的第一个单精度浮点数
    // printf("Result: %f\n", res[2]); // 打印结果寄存器中的第一个单精度浮点数
    // printf("Result: %f\n", res[3]); // 打印结果寄存器中的第一个单精度浮点数

    typedef struct {
        int age;
        int sex;
    } Stu;

    Stu s1 = { 24, 1999 };
    
    Stu *ps1 = &s1;
    printf("ps1 = %p\n", ps1);
    printf("ps1 + 1=%p\n\n", ps1 + 1);
    // ps1 指向 Stu 数据类型，Stu 8字节，那么 ps1+1 => ps1 + 1*8


    printf("ps1.age=%p", &ps1->sex);





    return 0;
}

typedef struct { 
    long a[2]; 
    long *p; 
} strA;

typedef struct {
    long u[2];
    long q;
} strB;

strB process(strA s) {
    strB r;
    r.u[0] = s.a[1];
    r.u[1] = s.a[0];
    r.q = *s.p;
    return r;
}
long eval(long x, long y, long z) {
    strA s;
    s.a[0] = x;
    s.a[1] = y;
    s.p = &z;
    strB r = process(s);
    return r.u[0] + r.u[1] + r.q;
}
