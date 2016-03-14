#include "FLOAT.h"

typedef long long int64_t;

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	int64_t res = (int64_t)a * (int64_t)b;	
	//nemu_assert(0);
	return res >> 16;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	unsigned int a00 = a << 16;
	unsigned int a01 = a >> 16;
	unsigned int a10 = a >> 31;
	unsigned int a11 = a >> 31;
	int ans = 0, i;
	for(i = 0; i < 64; ++i)
	{
		a11 = (a11 << 1) + (a10 >> 31);
		a10 = (a10 << 1) + (a01 >> 31);
		a01 = (a01 << 1) + (a00 >> 31);
		a00 = a00 << 1;
		ans = ans << 1;
		if(a11 > 0 || a10 >= b) {
			if(a10 < b) a11 --;
			a10 -= b;
			ans++; 
		}
	}
	return ans;
}

FLOAT f2F(float a) {
	//nemu_assert(0);
	return (int)(a * (1 << 16));
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

