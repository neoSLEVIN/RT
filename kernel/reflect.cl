
/*Отражение*/

/*
 Тут короч проблема что у нас может быть объект отражающий и прозрачный одновременно
 В этом случае из одного объекта выходят два луча.
		o
	   / \
	  o   o
		 / \
 через цикл это хз как сделать, поэтому руками прописал глубину 2 с учетом преломления и отражения
 то есть в зеркальном шаре будет отображаться другой зеркальный шар, в отражении которого будет просто цвета объектов без отражения и преломления.
 Лучше конечно проверьте и поэксперементируейте.
 С прозрачностью такая же история. Мы можем пройти только через 2 прозрачных объекта.
 
 Можно отказать от этих ограничений, но тогда объекты будут либо отражающие либо преломляющие.
 Тогда просто while(object[hit_id].material.reflect > 0)
 идем лучом пока отражается
 
 Жду ваших мнений
 Тут поднимается этот вопрос - https://stackoverflow.com/questions/42876586/reflection-and-refraction-impossible-without-recursive-ray-tracing
 но решение через стек какое-то непонятное
 */

float3 go_reflect(t_ray ray, t_scene *scene) {
	
	float3 finalColor = 0;
	
	/*цвет первого отраженного объекта*/
	finalColor = continue_reflect_ray(&ray, scene);
	if (ray.hit_id < 0)
		return (finalColor);
	/*простой объект*/
	if (scene->objects[ray.hit_id].material.transparency == 0 && scene->objects[ray.hit_id].material.reflective == 0) {
		return finalColor;
	}

	int i = -1;
	t_ray temp = ray;
	while (++i < scene->mirror && temp.hit_id >= 0)
	{
		t_ray temp2 = temp;
		/*объект отражает*/
		float ref = scene->objects[temp.hit_id].material.reflective;
		float trans = scene->objects[temp.hit_id].material.transparency;
		if (ref > 0) {
			finalColor = finalColor * (1.0f - ref) + continue_reflect_ray(&temp, scene) * ref;
			if (trans > 0) {
				finalColor = finalColor * (1.0f - trans) + continue_refract_ray(&temp2, scene) * trans;
			}
		} else if (trans > 0) {
			finalColor = finalColor * (1.0f - trans) + continue_refract_ray(&temp2, scene) * trans;
		} else {
			break ;
		}
	}

	 
	/*объект обладает прозрачностью*/
	float trans = scene->objects[ray.hit_id].material.transparency;
	if (trans > 0) {
		finalColor = finalColor * (1.0f - trans) + continue_refract_ray(&ray, scene) * trans;
	}
	
	return finalColor;
}

/*Меняет внутри луч*/
float3 continue_reflect_ray(t_ray *ray, t_scene *scene) {
	ray->dir = reflect(ray->dir, ray->hitNormal);
	ray->origin = ray->hitPoint + (ray->hitNormal * 0.01f);
	return send_ray(ray, scene);
}

float3 reflect_ray(t_ray ray, t_scene *scene) {
	ray.dir = reflect(ray.dir, ray.hitNormal);
	ray.origin = ray.hitPoint + (ray.hitNormal * 0.01f);
	return send_ray(&ray, scene);
}

float3 reflect(float3 rayDir, float3 targetNormal) {
	float3 tmp = 2.0f * dot(rayDir, targetNormal) * targetNormal;
	return rayDir - tmp;
}
