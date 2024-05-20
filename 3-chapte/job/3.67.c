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

    s.a[0] = 0;
    s.a[1] = 0;
    r.u[0] = 0;
    r.u[1] = 0;
    return r;
}
long eval(long x, long y, long z) {
    strA s;
    s.a[0] = 100;
    s.a[1] = 200;
    s.p = &z;
    strB r = process(s);

    printf("s.a[0]=%d\n", s.a[0]);
    printf("s.a[1]=%d", s.a[1]);

    return r.u[0] + r.u[1] + r.q;
}

void main() {
    eval(0xaabbccdd,0xaabbccdd,0xaabbccdd);
}