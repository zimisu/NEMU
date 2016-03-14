#include "FLOAT.h"

typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	uint64_t res = (uint64_t)a * (uint64_t)b;
	return res >> 16;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
    int sign = 1;
    if (a < 0) {
        sign *= -1;
        a = -a;
    }
    if (b < 0) {
        sign *= -1;
        b = -b;
    }
    int res = a / b;
    a = a % b;
    for (int i = 0; i < 16; i++) {
        a <<= 1;
        res <<= 1;
        if (a >= b) {
            a -= b;
            res++;
        }
    }
    return res * sign;
}



FLOAT f2F(float a) {	

	int i, uf, m, e, s, ans;
	uf = *(int*)&a;
	m = uf & ((1 << 23) - 1);
	e = ((uf >> 23) & ((1 << 8) - 1)) - 127;
	s = uf >> 31;
	ans = 1;
	for(i = 1; i <= e + 16; ++ i) {
		ans = (ans << 1) + ((m & (1 << 22)) >> 22);
		if (ans < 0) return 0x80000000u;
		m = m << 1;
	}
	if (s != 0) ans = (~ans) + 1;
	return (FLOAT)(ans);/*
	int i, m, e, s, ans;
	uint32_t f_uint = *(uint32_t*)&a;
	m = f_uint & 0x7fffff;
	e = ((f_uint >> 23) & ((1 << 8) - 1)) - 127;
	s = f_uint >> 31;
	ans = 1;
	for(i = 1; i <= e + 16; ++ i) {
		ans = (ans << 1) + ((m & (1 << 22)) >> 22);
		if (ans < 0) return 0x80000000u;
		m = m << 1;
	}
	if (s != 0) ans = (~ans) + 1;
	return (ans);*/
}

FLOAT Fabs(FLOAT a) {
	//nemu_assert(0);
	if (a < 0) return -a;
	return a;
}

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

