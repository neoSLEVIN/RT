
/*
 Лучше вместе еще разобрать
 http://viclw17.github.io/2018/12/28/Perlin-Noise-Implementation/
 http://eastfarthing.com/blog/2015-04-21-noise/
 */

/*рандомно перемешали 256 значений*/
constant int perm[] = {90,192,208,222,34,213,32,248,224,233,56,90,161,88,4,78,192,24,140,71,48,140,254,245,255,247,247,40,
185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
9,92,217,54,239,174,173,102,250,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
70,223,11,38,24,254,210,210,177,32,81,195,243,58,135,125,8,169,112,32,219,97,53,195,13,
203,9,47,104,125,117,114,139,124,165,203,181,235,209,206,70,127,180,174,0,167,181,41,
164,30,116,250,127,151,198,245,146,87,149,206,237,57,192,210,65,210,129,240,178,105,
228,108,245,148,140,40,35,195,38,65,207,215,253,65,85,208,76,62,3,237,55,89,
232,50,217,64,244,157,199,121,252,17,212,203,149,152,140,187,234,177,73,174,
193,100,231,143,97,53,145,135,19,103,13,135,199,91,239,247,33,39,145,
101,120,99,3,186,193,86,99,41,203,111,79,220,158,42,30,154,120,67,87,167,
135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,255,
114,20,218,113,154,27,246,1,8,198,92,173,21,102};

/*Функция аппроксиматор*/
float f( float t ) {
    t = fabs( t );
    return t >= 1.0f ? 0.0f : 1.0f - ( 3.0f - 2.0f * t ) * t * t;
}
/*накладываем градиент*/
float surflet( float x, float y, float grad_x, float grad_y ) {
    return f( x ) * f( y ) * ( grad_x * x + grad_y * y );
}

float noise(float x, float y) {
	
	float result = 0.0f;
	int cell_x = floor(x);
	int cell_y = floor(y);
	
	for (int grid_y = cell_y; grid_y <= cell_y + 1; grid_y++) {
		for (int grid_x = cell_x; grid_x <= cell_x + 1; grid_x++) {
			
			/*Мешаем hash*/
			int wtf0 = grid_x & 255;
			int wft1 = perm[wtf0];
			int wtf2 = wft1 + grid_y;
			int wtf3 = wtf2 & 255;
			int hash = perm[wtf3];
			/*нормализованный вектор градиента с сердины плитки до xy*/
			float grads_x = cos( 2.0f * M_PI * hash / 256);
			float grads_y = sin( 2.0f * M_PI * hash / 256);
			/*в цикле пробегаемся по 4ем соседям и складываем значения - то как на нас влияют ближайшие*/
			float tmp = surflet(x - grid_x, y - grid_y, grads_x, grads_y);
			result += tmp;
		}
	}
	/*(-1;1)*/
	return result;
}

/*size - то насколько частей мы разбиваем uv*/
float3 typical_noise(t_object *obj, float2 uv, int size) {
	float n = noise(uv.x * size, uv.y * size);
	n = 0.5f * (n + 1.0f);
	return obj->material.color * n;
}

float3 wood(t_object *obj, float2 uv, int size) {
	float n = 20 * noise(uv.x * size, uv.y * size);
	n = n - floor(n);
	return obj->material.color * n;
}

/*
 Можно добавить интересные текстуры
 но пока не допер как
 https://lodev.org/cgtutor/randomnoise.html
 через turbulence
 */
