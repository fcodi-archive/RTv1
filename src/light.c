#include <RTv1.h>

t_light 	*new_light(void)
{
	t_light		*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	init_point3d(&light->pos);
	light->intensive = 0.0;
	light->type = light_type_none;
	return (light);
}

static void		closest_object_light(t_point3d vec_l, int type, t_scene *scene)
{
	t_root		root;
	int         i;

	i = 0;
	scene->math->closest_obj_2 = NULL;
	if (type == directional)
		scene->math->closest_t_2 = MAX;
	else
		scene->math->closest_t_2 = 1;
	while (scene->object[i])
	{
		root = hit_obj(vec_l, scene->math->point, scene->object[i]);
		if (root.a > MIN && root.a < MAX && root.a < scene->math->closest_t_2)
		{
			scene->math->closest_t_2 = root.a;
			scene->math->closest_obj_2 = scene->object[i];
		}
		if (root.b > MIN && root.b < MAX && root.b < scene->math->closest_t_2)
		{
			scene->math->closest_t_2 = root.b;
			scene->math->closest_obj_2 = scene->object[i];
		}
		i++;
	}
}

static void		point_direct_light_math(double *intensive, t_light *tmp,
                                           t_point3d view, t_scene *scene)
{
	double		r_dot_v;
	double		n_dot_l;
	t_point3d	vec_l;
	t_point3d	vec_r;

	if (tmp->type == point)
		vec_l = ft_vec_subtract(tmp->pos, scene->math->point);
	else
		vec_l = tmp->pos;
	closest_object_light(vec_l, tmp->type, scene);
	if (scene->math->closest_obj_2)
		return ;
	n_dot_l = ft_vec_dot(scene->math->normal, vec_l);
	if (n_dot_l > 0)
		*intensive += tmp->intensive * n_dot_l
		              / (ft_vec_length(scene->math->normal) * ft_vec_length(vec_l));
	if (scene->math->closest_obj->specular != -1)
	{
		vec_r = ft_vec_subtract(ft_vec_multiplication_num(scene->math->normal, 2
		                                                                    * ft_vec_dot(scene->math->normal, vec_l)), vec_l);
		r_dot_v = ft_vec_dot(vec_r, view);
		if (r_dot_v > 0)
			*intensive += tmp->intensive * pow(r_dot_v / (ft_vec_length(vec_r)
			                                              * ft_vec_length(view)), scene->math->closest_obj->specular);
	}
}

double			compute_light(t_point3d view, t_scene *scene)
{
	double		intensive;
	int         i;

	intensive = 0;
	i = 0;
	while (scene->light[i])
	{
		if (scene->light[i]->type == ambient)
			intensive += scene->light[i]->intensive;
		else
			point_direct_light_math(&intensive, scene->light[i], view, scene);
		i++;
	}
	intensive > 1.0 ? intensive = 1.0f : 0;
	return (intensive);
}