

float2	cut_by_sphere_section(t_ray *ray,
							float3 section_pos, float section_radius,
							float2 new_t)
{
	float3		new_origin;
	float		coef[3];
	float		discriminant;

	/* Находим точки пересечения сферы сечения и луча камеры.
       P.S. На этом же луче лежат одна/две точки пересечения фигуры с этим лучом. */
	new_origin = ray->origin - section_pos;
	coef[0] = dot(ray->dir, ray->dir);
	coef[1] = 2.0f * dot(ray->dir, new_origin);
	coef[2] = dot(new_origin, new_origin) - section_radius * section_radius;
	discriminant = coef[1] * coef[1] - 4.0f * coef[0] * coef[2];

	/* Если сечение не пересекается с фигурой, то точки фигуры видны. */
	if (discriminant < 0.0f)
		return (new_t);

	float t[2];
	t[0] = (-coef[1] - sqrt(discriminant)) / (2.0f * coef[0]);
	t[1] = (-coef[1] + sqrt(discriminant)) / (2.0f * coef[0]);

	float min_t = t[0] < t[1] ? t[0] : t[1];
	float max_t = t[0] > t[1] ? t[0] : t[1];

	/* Если точка фигуры находится между точками сечения, то эту точку мы не видим,
	    поэтому этой точке ставим значение t = -1 */
	if (new_t.x - min_t >= -0.0005f && new_t.x - max_t <= 0.0005f)
		new_t.x = -1.0f;
	if (new_t.y - min_t >= -0.0005f && new_t.y - max_t <= 0.0005f)
		new_t.y = -1.0f;
	return new_t;
}

float2	cut_by_plane_section(float3 *t_point,
							float3 section_pos, float3 section_dir,
							float2 new_t)
{
	float3 section_to_t[2];

	/* Находим вектора, направленные из центра плоскости сечения (section_pos)
	    к точкам пересечения фигуры с лучом из камеры (t_point[i]) */
	section_to_t[0] = t_point[0] - section_pos;
	section_to_t[1] = t_point[1] - section_pos;

	/* Если вектор section_to_t[i] находится с той же стороны плоскости сечения,
	    что и её нормаль(представим, что нормаль выходит из центра сечения),
	    то точка фигуры, в которую направлен вектор section_to_t[i],
	    отсекается данным сечением, поэтому этой точке ставим значение t = -1,
	    что равноценно тому, что мы её не видим */
	if (dot(section_to_t[0], section_dir) >= 0.01f)
		new_t.x = -1.0f;
	if (dot(section_to_t[1], section_dir) >= 0.01f)
		new_t.y = -1.0f;
	return new_t;
}

/* Комплексные сечения создают область из пересечений друг с другом(некий абстрактный объект).
   Внутри этой области(этого объекта) будут отсекаться все точки фигуры */
float	compute_complex_sections(t_ray *ray, t_section *sections,
								float3 *t_point, float2 old_t)
{
	/* t - будет результирующим значением, определяющим на каком растоянии от луча камеры
	       находится ближайшая видимая точка пересечения с фигурой.
	       Если t <= 0, то точку фигуры мы не видим. */
	float	t = -1.0f;

	int i = 0;
	/* Важно понять:
	   Чтобы определить, отсечены ли точки фигуры областью из комплексных сечений,
	   нужно рассматривать каждое сечение по отдельности, и если хотя бы в одном из случаев
	   мы видим точку, то это означает, что точка находится вне области комплексных сечений */
	while (i < 6) {
		if (sections[i].on) {
			/* В данном случае функция будет возвращать нам два значения:
			    точки t1 и t2 фигуры. НО если точка отсечена, то по ней вернется -1.
			   Если точка сзади нас или мы стоим на ней,
			    то, соответственно, её t <= 0 */
			float2 temp_t;
			if (sections[i].type == PLANE) {
				temp_t =
					cut_by_plane_section(t_point,
										 sections[i].position,
										 sections[i].direction,
										 old_t);
			} else {
				temp_t =
					cut_by_sphere_section(ray,
										  sections[i].position,
										  sections[i].radius,
										  old_t);
			}
			/* Затем, Во втором аргументе получаем ближайшую видимую точку для случая
			    с одним текущим сечением.
			   Если это сечение обрезало нам обе точки, то это еще не означает,
			    что мы не увидим фигуру через луч.
			   Наша задача проверить, видим ли мы точку фигуры при других сечениях.
			   Переменная t как раз хранит информацию о ближайшей видимой точке.
			   Поэтому мы просто её перезапишем, если вторым аргументом получим
			    видимую точку поближе */
			t = minT(t, minT(temp_t.x, temp_t.y));
		}
		i++;
	}
	return t;
}

/* Обычные сечения проще, чем комплексные.
   Если одно из сечений обрезало точку, то мы её 100% не увидим. */
float	compute_simple_sections(t_ray *ray, t_section *sections,
								float3 *t_point, float2 new_t)
{
	int i = 0;
	while (i < 6) {
		if (sections[i].on) {
			/* В первой итерации в new_t содержатся значения двух точек - t1 и t2.
			   Так как достаточно обрезать точку одним из сечений, то можем смело
			    перезаписывать new_t. Перезапись будет в случае,
			    если какая-то из точек отсечена, тогда её t примет значение -1 */
			if (sections[i].type == PLANE) {
				new_t =
					cut_by_plane_section(t_point,
										 sections[i].position,
										 sections[i].direction,
										 new_t);
			} else {
				new_t =
					cut_by_sphere_section(ray,
										sections[i].position,
										sections[i].radius,
										new_t);
			}
			/* Если оба значения t - отрицательные,
			    то на луче мы точно не пересечемся с фигурой,
			    поэтому нет смысла проверять другие сечения. */
			if (new_t.x <= 0 && new_t.y <= 0)
				return -1.0f;
		}
		i++;
	}
	/* Если мы дошли сюда, значит хотя бы одна из точек видна лучу.
	   Возвращаем ближайшую видимую. */
	return minT(new_t.x, new_t.y);
}

float	compute_sections(t_ray *ray, t_section *sections, int is_complex,
						float t1, float t2)
{
	float2	two_t = (float2)(t1, t2);
	float3	t_point[2];

	t_point[0] = ray->origin + t1 * ray->dir;
	t_point[1] = ray->origin + t2 * ray->dir;
	if (is_complex)
		return compute_complex_sections(ray, sections, t_point, two_t);
	return compute_simple_sections(ray, sections, t_point, two_t);
}
