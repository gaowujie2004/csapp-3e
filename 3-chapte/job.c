#include <stdio.h>

void show_bytes(unsigned char* ptr, short size) {
    // ptr <-> byte [ptr]
    printf("0x");
    for (int i = 0; i < size; i++) {
        // ptr[i] <-> *(ptr+i) <-> mov ah [ptr+i]
        printf("%.2x ", ptr[i]);
    }
}


void show_binary_bytes(unsigned char* ptr, short size) {
    printf("0B");
    for (int i = 0; i < size; i++) {
        show_binary(ptr[i]);
        printf(" ");
    }
}
void show_binary(unsigned char num) {
    for (int i = 7; i >= 0; i--) {
        if (num & (1 << i)) {
            printf("1");
        } else {
            // 0, 那该为就是0
            printf("0");
        }
    }
}


void show_short(short num) {
    show_bytes((unsigned char*)&num, sizeof(num));
}

void show_long(long long num) {
    show_bytes((unsigned char*)&num, sizeof(long long));
}

void show_binary_n(unsigned int x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        if (x & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

void show_float(float num) {
    // 小端
    unsigned char* ptr = (unsigned char*)&num;

    // 符号字段(32)
    unsigned char  sign = ptr[3] >> 7;

    //exp 阶码字段(24-31)
    unsigned char exp_low_1 = ptr[2] >> 7;
    unsigned char exp_heig_7 = ptr[3] << 1;
    unsigned char exp = exp_heig_7 | exp_low_1;

    //frac 小数字段(1-23)
    unsigned int frac = *((unsigned int*)ptr) & 0x7FFFFF;


    show_binary_n(sign, 1);
    printf(" ");

    show_binary_n(exp, 8);
    printf(" ");

    show_binary_n(frac, 23);

}




void show_double(double num) {
    show_binary_bytes((unsigned char*)&num, sizeof(double));
}


int is_little_endian() {
    short num = 0x1234;
    unsigned char singleNum = *(unsigned char*)&num;
    //在使用时，将这样CPU寻址: byte [ptr]，若不转换类型，则是 word [ptr]
    return singleNum == 0x34;
}
int is_little_endian2() {
    typedef union {
        short a;
        unsigned char single;
    } Test;

    Test num;
    num.a = 0x1234;

    // num.single 类型是char，故使用时会byte [ebp+n]
    return num.single == 0x34;
}

unsigned __int64 double2bits(double d)
{
    union {
        double d;
        unsigned __int64 u
    } temp;
    temp.d = d;
    return temp.u;
};

int main()
{
    unsigned __int64 bits = double2bits(4.0);
    show_binary_bytes((char *)&bits, sizeof( unsigned __int64));
    
    printf("\n\nshow_double=");
    show_double(4.0);
    return 0;
}

