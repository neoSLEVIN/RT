
uint xorshift32(uint *state)
{
	uint x = *state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return *state = x;
}

/*получаем в промежутке [0;1]*/
float get_random(uint *state)
{
	float res;
	uint rnd = xorshift32(state);
	res = (float)rnd / 4294967295;
	return res;
}
