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

unsigned replace_byte(unsigned x, int i, unsigned char b) {
    // TODO: 边界条件
    int mask = ~(0xff << i * 8);

    // 把指定为清零
    return (x & mask) | (b << i * 8);
}


// C语言，int类型数右移是否采用算术右移？
int int_shifts_are_arithmetic() {
    return -1 >> 1 == -1;
}

// srl用算术右移来完成逻辑右移
unsigned int srl(unsigned int x, int k) {
    unsigned int xsra = (int)x >> k;
    // 以后的操作不能包括：右移、除法
    // 核心思路：xsra的高k位变为0，因为要实现逻辑右移

    // 1111......，右移k位，高k位就为0，但现在不能使用右移运算。
    // 下面就是模拟上面的功能
    unsigned int mask = ~(-1 << (8 * sizeof(int) - k));       // -1的高k位为0
    return xsra & mask;
}


// sra用逻辑右移来完成算术右移，感觉有点难
unsigned int sra(int x, int k) {
    int xsra = (unsigned)x >> k;
    // 以后的操作不能包括：右移、除法
    // 核心思路：xsra的高k位变为符号位的值，因为要实现算术右移

    // 获取x的最高位的值
    // 没有任何头绪了......
}


/*当 x 的任何奇数位等于 1 时，返回 1; 假设int类型是32位 */
int any_odd_one(unsigned x) {
    int mask = 0x55555555;  // 0101
    return x & mask == mask;
}


/*当x包含奇数个1时返回1，否则返回0*/
/*目前只能想到这里了，只能用一个哨兵顺序检查二进制序列了*/
int odd_ones(unsigned x) {
    int resCount = 0;
    int mask = 1;

    resCount += !!(x & mask); //判断第1位

    mask << 1;
    resCount += !!(x & mask); //判断第2位

    // .......
}


/*
* 生成最左边的1，相当于提取最左边的1，然后右边的全清零。假设int是32位
* 例如：0xFF00 -> 0x8000、0x6600->0x4000
*/
int leftmost_one(unsigned x) {
    //思路：判断最左边的1位于第几位，记住k（从1开始）然后逻辑右移k，再左移k位
    //这似乎不行，因为要用到分支语句了。
}




/*
* 掩码，最低n位设置为1
* 例子：n=6 --> 0x3F、n=17 --> 0x1FFFF
*/
int lower_one_mask(int n) {
    // 左移w-n位，再逻辑右移w-n位
    int shiftCount = sizeof(int) * 8 - n;
    return (unsigned)(-1 << shiftCount) >> shiftCount;
}


/*
* 左移循环, 0 <= n < w
* 例子：当x=0x12345678，n=4 --> 0x23456781； n=20 --> 0x67812345
*/
unsigned rotate_left(unsigned x, int n) {
    // 左移溢出的
    int right = x >> (sizeof(x) * 8 - n);
    int left = x << n;

    return left | right;
}

/*
* Return 1 when x can be represented as an n-bit,2's-complement number;0 otherwise
* 如果x可以表示为n位2的补数，则返回1，否则返回0
*/
int fits_bits(int x, int n) {

}


typedef unsigned packed_t;
int xbyte(packed_t word, int bytenum) {

}


/*
* 饱和加法运算，正溢出时返回TMax、负溢出时返回TMin
*/
int saturating_add(int x, int y) {
    //用以往的思路，那就是判断是否溢出，要用到分支语句，但该题不能使用。
    int sum = x + y;

    int up_overflow = y > 0 && y > 0 && sum < 0;
    int down_overflow = x < 0 && y < 0 && sum>0;

    return 2;
}

/* 结果不溢出就返回1，反之则0 */
// int tsub_ok(int x, int y) {
//     int sub_res = x - y;
//     return (x>0 && y>0) || (x<0 && y<0) ||  (x<=0 && y>=0 && sub_res<=0) || (x=>0 && y<=0 && sub_res>= 0);
// }

void test_hh(unsigned num) {
    if (num >= 0) {
        printf("红红火火恍恍惚惚很好");
    }
}

// void *malloc(size_t size);
// void *menset(void *s, int c, size_t n);
// /**
//  * 分配内存、再将这块内存设置为0
// */
// void *calloc(size_t nmemb, size_t size) {
//     if (nmemb == 0 || size == 0) {
//         return NULL;
//     }

//     unsigned int menb_size = nmemb*size; //无符号乘法，问题可能出在这里
//     void *ptr = malloc(menb_size); 
//     void *zeroPtr = menset(ptr, 0, menb_size);

//     return zeroPtr; // ?不太确定啊
// }


/**
 * 2.78：该函数要用正确的舍入方式计算 x/2^k，并且应该遵循位级整数编码规则。
 * 难度：**（2星）
 * 详解：
 *      对于x=负数，需向上舍入，就等于 (x+y-1)/y，对于该题 (x+2>>k-1)/y
 *      2>>k - 1，此结果很特殊，它的位级表示为k个1
*/
int divide_power2(int x, int k) {
    int w = sizeof(int) << 3;

    int mask = (unsigned)~0 >> (w - k);                    //右移表示给左边腾地方，腾出w-k个位
    int bias = (x >> (w - 1)) & mask;                    //偏置常量.
    //            取得符号位   &  mask，保留k位

    return (x + bias) >> k;
    // test case:
    // printf("16/2**3=%d\n", divide_power2(16, 3));
    // printf("17/2**3=%d\n", divide_power2(17, 3));
    // printf("18/2**3=%d\n", divide_power2(18, 3));

    // printf("-16/2**3=%d\n", divide_power2(-16, 3));
    // printf("-17/2**3=%d\n", divide_power2(-17, 3));
    // printf("-18/2**3=%d\n", divide_power2(-18, 3));
}



/**
 * 2.80: 写出函数threefourths的代码，对于整数参数x，计算3/4x的值，向零舍人。它不会溢出。函数应该遵循位级整数编码规则
 * 难度: ***（3星）
 * 详解：与练习题2.78类似
 * 思考：x<<2 - 1，即4*x - 1位级表示有什么特别的吗？
 * 不会
*/
int threefourths(int x) {
    int w = sizeof(int) << 3;

    // 4*x，其中x是整数，它怎么用2的n次幂来表示？
}


/**
 * 2.81：编写C表达式产生如下位模式，其中 a^k 表示符号a重复k次。假设一个w位的数据类型。代码可以包含对参数j和k的引用，它们分别表示j和k的值，但是不能使用表示 w 的参数。
 * 要求：A
 * 难度：**（2星）
*/
int job_2_81_a(int k) {
    // 左移k位，右边就空出k个0
    return ~0 << k;
}

/**
 * 2.81：编写C表达式产生如下位模式，其中 a^k 表示符号a重复k次。假设一个w位的数据类型。代码可以包含对参数j和k的引用，它们分别表示j和k的值，但是不能使用表示 w 的参数。
 * 要求：B。 0^(w-k-j) 1^k 0^j
 * 难度：**（2星）
 * 不会
*/
// int job_2_81_,b(int k, int j){
//     // 左移k位，右边就空出k个0
//     // 将k位设为1，
// }


/**
 * 2.92：遵循位级浮点编码规则。
 * 对于浮点数f，此函数计算 -f。如果 f 是 NaN，此函数简单地返回 f。
 * 测试你的函数，对参数 f 可以取的所有2^32个值求值，将结果与你使用机器的浮点运算得到的结果相比较
 * 难度：**（2星）
*/
typedef unsigned int float_bits;

float_bits float_negate(float_bits f) {
    int exp_bits = (f >> 23) & 0xFF;  //丢掉符号位
    int frac_bits = f & 0x7FFFFF;

    if (exp_bits == 0xFF && frac_bits != 0) {
        // NaN
        return f;
    } else {
        // 将某一位取反，那就先获取这位值。异或
        return f ^ 0x80000000;
    }
}
void test_float_negate() {
    float f1 = 0.5;
    float_bits *pf1 = (void *)&f1;
    unsigned res1 = float_negate(*pf1);
    float *pres1 = (void *)&res1;
    show_float(*pres1);
    printf("\n");

    unsigned res2 = float_negate(~0);
    float *pres2 = (void *)&res2;
    show_float(*pres2);


}


/**
 * 2.93：遵循位级浮点编码规则。
 * 对于浮点数f，此函数计算 |f|。如果f是NaN，此函数简单地返回f。
 * 测试你的函数，对参数 f 可以取的所有2^32个值求值，将结果与你使用机器的浮点运算得到的结果相比较
 * 难度：**（2星）
*/
float_bits float_absval(float_bits f) {
    int sign = f >> 31;
    int exp = (f >> 23) & 0xFF;  //丢掉符号位
    int frac = f & 0x7FFFFF;

    if (exp == 0xFF && frac != 0) {
        // NaN
        return f;
    } else {
        // 将某一位取反，那就先获取这位值。异或
        return f & 0x7FFFFFFF;
    }
}


/**
 * 2.94：遵循位级浮点编码规则。
 * 对于浮点数f，这个函数计算2.0·f。如果f是NaN,你的函数应该简单地返回f。
 * 测试你的函数，对参数∫可以取的所有232个值求值，将结果与你使用机器的浮点运算得到的结果相比较。
 * 难度：***（3星）
*/
float_bits float_twice(float_bits f) {
    /**
     * 易错：可不能直接f*2，因为它的类型是unsigned int，而不是float或double，
     * 使用的指令是mul，而不是浮点乘法指令，本质上是由于整数和浮点数的存储格式不一致造成的。
    */

    /**
     * 算法：
     * 1、指数部分相加，M（有效位数）相乘
     * 2、如有需要对积进行规格化：积右移，指数增加
     * 3、指数是否溢出？若溢出则完成，没溢出进行下一步
     * 4、将尾数（f）舍入到合适的位置
     * 5、若还是非规格化，则跳转到2；否则返回结果
    */
    unsigned int sign = f >> 31;
    unsigned int exp = (f >> 23) & 0xFF;
    unsigned int frac = f & 0x7FFFFF;

    // 1 <= exp <= UMax-1   --->   1 <= exp <= 254
    if (exp == ~0) {
        // NaN or 无穷大
        return f;
    }



    // unsigned int res_exp = exp + 1;
    // 因为这是一个2，小数部分不会相乘。
    
    if (exp == 254) {
        // 指数溢出，无穷大
        exp = ~0;
        frac = 0;
    } else {
        // 正常范围
        exp++;
    }

    return (sign << 31) | (exp << 23) | frac;
}
void test_float_twice() {
    float f1 = 0.5;
    float_bits *pf1 = (void *)&f1;
    unsigned res1 = float_twice(*pf1);
    float *pres1 = (void *)&res1;
    
    printf("0.5*2 float_twice res  = ");
    show_float(*pres1);
    printf("\n");

    printf("0.5*2 ok res           = ");
    show_float(0.5*2.0);
    printf("\n");
}




/**
 * 2.95：遵循位级浮点编码规则。
 * 目标：对于浮点数f，这个函数计算0.5·f。如果f是NaN，你的函数应该简单地返回f。测试你的函数，对参数f可以取的所有2^32个值求值，将结果与你使用机器的浮点运算得到的结果相比较。
 * 难度：***（3星）
*/
float_bits float_half(float_bits f) {
    unsigned int sign = f >> 31;
    unsigned int exp = (f >> 23) & 0xFF;
    unsigned int frac = f & 0x7FFFFF;

    // 1 <= exp <= UMax-1   --->   1 <= exp <= 254
    // NaN or 无穷大
    if (exp == ~0) {
        return f;
    }


    if (exp == 1) {
        // 非规格化
        
    } else {
        // 正常范围
        exp--;
    }

    return (sign << 31) | (exp << 23) | frac;
}


/**
 * 2.96：遵循位级浮点编码规则。
 * 目标：对于浮点数f，这个函数计算(int)f。如果f不能用整数表示(例如，超出表示范围，或者它是一个 NaN)，则函数应该返回0x8000_0000。测试你的函数，对参数f可以取的所有2^32个值求值，将结果与你使用机器的浮点运算得到的结果相比较。
 * 难度：****（4星）
 * 可移植性：默认int=4byte，float=32位（1位符号位、8位阶码位、23位小数位）
*/
const int INT_BIT_SIZE = 4*8;
int float_f2i(float_bits f) {
    unsigned int sign = f >> 31;
    unsigned int exp = (f >> 23) & 0xFF;
    unsigned int frac = f & 0x7FFFFF;
    int res_int = 0;

    // NaN or 无穷
    if (exp == ~0) {
        return 0x80000000;
    }

    // 0、非规格化、指数为0
    if (exp < 127) {
        // E=exp-127，E<0则说明符浮点数<1.0，是个很小的浮点数
        return 0;
    }

    // E>=0
    int need_frac_num = exp - 127;  // E
    unsigned int low = frac >> (23-need_frac_num);
    unsigned int heig = 1 << need_frac_num;
    res_int = heig | low;
    
    if (sign) {
        return -res_int;
    } else {
        return res_int;
    }
}


/**
 * 2.97：遵循位级浮点编码规则。
 * 目标：对于函数i，这个函数计算(float)i的位级表示。测试你的函数，对参数f可以取的所有2^32个值求值，将结果与你使用机器的浮点运算得到的结果相比较。
 * 难度：****（4星）
 * 可移植性：默认int=4byte，float=32位（1位符号位、8位阶码位、23位小数位）
*/
float_bits float_i2f(int num) {
    unsigned int sign = (unsigned)num >> 31;
    unsigned int exp = 0;
    unsigned int frac = 0;

    // 从最高位开始，找到第一个1位的位置。
    int i=0;
    for (; i<32; i++) {
        int m_bit = (unsigned)(num << i) >> 31;
        if (m_bit) {
            break;
        } else {
            // continue;
        }
    }
    
    
    int E = 31-i;
    exp = E + 127;
    // 有符号exp不可能小于0
    // 不存在非规格化的情况（除了0），但因为int型最小就是0，没有0.xxx。
    if (num == 0) {
        frac = 0;
        exp = 0;
    }


    // int32，有32位，而float小数部分只能存储23位+隐藏的前导1，一共24位。故此涉及到舍入
    if (E > 23) {
        /**
         * 舍入算法。对于num，从左到右数到第一个1的位置，再加上23。这就是M的位数了，剩下的就是要超出的，将他们与0b1000...(位数和剩下要超出的位数一致)相比
         * 小于则不进位。大于则进位。等于则判断最低位是否是偶数（0），若位偶数则不进位，若为奇数（1）则最低位进位
         * 例子：11111111 11111111 11111111 10000000
         *       00001111 11111111 11111111 0111 0100     E=32-5=27、rounding_count=27-23=4
        */
        unsigned int rounding_count = E-23; //23位小数右侧多余放不下的位数
        unsigned int rounding_num = num & ~(~0 << rounding_count);
        unsigned int base = 1 << (rounding_count-1);
        


        if (rounding_num < base) {  // 23位的最低位不进位
            unsigned int frac_num =  num & ~(1 << E);   //num最左边1的掩码，干掉左边第一个1。
            frac = frac_num >> rounding_count;
        } else if (rounding_num > base) {    // 23位的最低位进位
            unsigned int M_uint = (unsigned int)num >> rounding_count;  // M_uint只占用24位
            
            // 检查M_uint最高位是否进位，只有当M_uint全为1时，最高位才会进位
            if (M_uint == (-1 >> (32-24))) {
                // 进位后，最高位也进位
                exp++;
                E++;
                M_uint++;
                // M_uint变为25位
                M_uint = (M_uint << 8) >> 9;

            } else {
                M_uint++;
            }

        } else {
            //TODO
        }
    } else {
        // 不舍入
        unsigned int frac_uint =  num & ~(1 << E);   //num最左边1的掩码，干掉左边第一个1。
        frac = frac_uint << (23-E);                  //0.10000，1后面的0
    }
    
}

int main() {
    unsigned int x = 0B11111111111111111111111110000000;
    unsigned int y = (float)x;
    printf("转为浮点，再转int=%u\n", y);
    show_float((float)x);
    return 0;
}



