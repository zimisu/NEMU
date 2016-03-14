#include "trap.h"
#include "FLOAT.h"

/* solve 0.5x^2 + 0.5x - 0.5 = 0 */

int main() {
	FLOAT a = f2F(0.5);
	FLOAT b = f2F(0.5);
	FLOAT c = f2F(-0.5);
	FLOAT a_plus_b = f2F(1.0);
	nemu_assert(a + b == a_plus_b);
	//set_bp();
	nemu_assert(f2F(0.25) == F_mul_F(a, b));
	//set_bp();
	nemu_assert(f2F(1) == F_div_F(a, b));
	//set_bp();
	nemu_assert(f2F(1.0) == Fabs(-1.0) && Fabs(1.0) == f2F(5.4) - f2F(-3.6) - f2F(8.0));
	set_bp();

	FLOAT dt = F_mul_F(b, b) - F_mul_F(F_mul_int(a, 4), c);
	FLOAT sqrt_dt = sqrt(dt);

	FLOAT x1 = F_div_F(-b + sqrt_dt, F_mul_int(a, 2));
	FLOAT x2 = F_div_F(-b - sqrt_dt, F_mul_int(a, 2));

	FLOAT x1_ans = f2F(0.618);
	FLOAT x2_ans = f2F(-1.618);

	nemu_assert(Fabs(x1_ans - x1) < f2F(1e-4));
	nemu_assert(Fabs(x2_ans - x2) < f2F(1e-4));

	HIT_GOOD_TRAP;
	return 0;
}
