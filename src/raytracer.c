t_vector		cone_normal(t_obj *obj, t_vector point)
{
	t_vector	normal;
	double		m;
	double		k;

	k = (1 + obj->radius * obj->radius);
	m = ft_vec_dot(ft_vec_subtract(point, obj->pos), obj->dir);
	normal = ft_vec_multiplication_num((obj->dir), (float)(m * k));
	normal = ft_vec_subtract(ft_vec_subtract(point, obj->pos), normal);
	normal = ft_vec_multiplication_num(normal,
	                                   (double)(1.f / ft_vec_length(normal)));
	return (normal);
}

t_vector		cylinder_normal(t_obj *obj, t_vector point)
{
	t_vector	normal;
	double		m;

	m = ft_vec_dot(ft_vec_subtract(point, obj->pos), obj->dir);
	obj->dir = ft_vec_multiplication_num(obj->dir,
	                                     (double)(1.f / ft_vec_length(obj->dir)));
	normal = ft_vec_multiplication_num(obj->dir, m);
	normal = ft_vec_subtract(ft_vec_subtract(point, obj->pos), normal);
	normal = ft_vec_multiplication_num(normal,
	                                   (double)(1.f / ft_vec_length(normal)));
	return (normal);
}

t_vector		sphere_normal(t_obj *obj, t_vector point)
{
	t_vector	normal;

	normal = ft_vec_subtract(point, obj->pos);
	normal = ft_vec_multiplication_num(normal,
	                                   (double)(1.f / ft_vec_length(normal)));
	return (normal);
}

t_vector		plane_normal(t_obj *obj, t_vector point)
{
	t_vector	normal;

	normal = obj->dir;
	return (normal);
}

t_vector		get_normal(t_obj *obj, t_vector point)
{
	if (obj->type == Cone)
		return (cone_normal(obj, point));
	if (obj->type == Cylinder)
		return (cylinder_normal(obj, point));
	if (obj->type == Sphere)
		return (sphere_normal(obj, point));
	if (obj->type == Plane)
		return (plane_normal(obj, point));
	return ((t_vector){0, 0, 0});
}

void			closest_object(t_rt *rt)
{
	t_root		root;
	t_obj		*tmp;

	tmp = rt->obj;
	rt->math->closest_obj = NULL;
	rt->math->closest_t = MAX;
	while (tmp)
	{
		root = hit_obj(rt->math->dir, rt->camera, tmp);
		if (root.a > MIN && root.a < MAX && root.a < rt->math->closest_t)
		{
			rt->math->closest_t = root.a;
			rt->math->closest_obj = tmp;
		}
		if (root.b > MIN && root.b < MAX && root.b < rt->math->closest_t)
		{
			rt->math->closest_t = root.b;
			rt->math->closest_obj = tmp;
		}
		tmp = tmp->next;
	}
}

t_vector		calculate_direction(int x, int y, int width, int height)
{
	t_vector	dir;

	dir.x = (double)x * 1.15 / width;
	dir.y = (double)y * 0.64 / height;
	dir.z = 1;
	return (dir);
}

t_root			hit_cone(t_vector dir, t_vector camera, t_obj *cone)
{
	t_vector	res;
	float		discrim;
	t_root		root;
	float		k;

	k = 1 + cone->radius * cone->radius;
	res.x = ft_vec_dot(dir, dir) - k * pow(ft_vec_dot(dir, cone->dir), 2.0);
	res.y = 2 * (ft_vec_dot(dir, ft_vec_subtract(camera, cone->pos)) -
	             k * ft_vec_dot(dir, cone->dir) *
	             ft_vec_dot(ft_vec_subtract(camera, cone->pos), cone->dir));
	res.z = ft_vec_dot(ft_vec_subtract(camera, cone->pos),
	                   ft_vec_subtract(camera, cone->pos)) - k
	                                                         * pow(ft_vec_dot(ft_vec_subtract(camera, cone->pos),
	                                                                          cone->dir), 2);
	discrim = res.y * res.y - (4.0f * res.x * res.z);
	if (discrim < 0)
		return (t_root){-1, -1};
	root.a = ((-res.y + sqrtf(discrim)) / (2.0 * res.x));
	root.b = ((-res.y - sqrtf(discrim)) / (2.0 * res.x));
	return (root);
}

t_root			hit_cylinder(t_vector dir, t_vector camera, t_obj *cylinder)
{
	t_vector	res;
	double		discrim;
	t_root		root;

	res.x = ft_vec_dot(dir, dir) - pow(ft_vec_dot(dir, cylinder->dir), 2.0);
	res.y = (ft_vec_dot(dir, ft_vec_subtract(camera, cylinder->pos))
	         - ft_vec_dot(dir, cylinder->dir)
	           * ft_vec_dot(ft_vec_subtract(camera, cylinder->pos),
	                        cylinder->dir)) * 2.0;
	res.z = ft_vec_dot(ft_vec_subtract(camera, cylinder->pos),
	                   ft_vec_subtract(camera, cylinder->pos))
	        - pow(ft_vec_dot(ft_vec_subtract(camera, cylinder->pos),
	                         cylinder->dir), 2)
	        - (cylinder->radius * cylinder->radius);
	discrim = res.y * res.y - (4.0 * res.x * res.z);
	if (discrim < 0)
		return (t_root){-1, -1};
	root.a = ((-res.y + sqrt(discrim)) / (2.0 * res.x));
	root.b = ((-res.y - sqrt(discrim)) / (2.0 * res.x));
	return (root);
}

t_root			hit_sphere(t_vector dir, t_vector camera, t_obj *sphere)
{
	t_root		root;
	t_vector	oc;
	t_vector	res;
	double		discrim;

	oc = ft_vec_subtract(camera, sphere->pos);
	res.x = ft_vec_dot(dir, dir);
	res.y = 2 * ft_vec_dot(oc, dir);
	res.z = ft_vec_dot(oc, oc) - sphere->radius * sphere->radius;
	discrim = res.y * res.y - 4 * res.x * res.z;
	if (discrim < 0)
		return (t_root){-1, -1};
	root.a = ((-res.y + sqrt(discrim)) / (2.0 * res.x));
	root.b = ((-res.y - sqrt(discrim)) / (2.0 * res.x));
	return (root);
}

t_root			hit_plane(t_vector dir, t_vector camera, t_obj *plane)
{
	t_root		root;

	root = (t_root){-1, -1};
	if (plane->dir.x != 0
	    || plane->dir.y != 0
	    || plane->dir.z != 0)
		root.a = ft_vec_dot(plane->dir,
		                    ft_vec_subtract(plane->pos, camera))
		         / ft_vec_dot(plane->dir, dir);
	root.b = -1.0;
	return (root);
}

t_root			hit_obj(t_vector dir, t_vector camera, t_obj *obj)
{
	if (obj->type == Sphere)
		return (hit_sphere(dir, camera, obj));
	else if (obj->type == Plane)
		return (hit_plane(dir, camera, obj));
	else if (obj->type == Cone)
		return (hit_cone(dir, camera, obj));
	else if (obj->type == Cylinder)
		return (hit_cylinder(dir, camera, obj));
	return (t_root){-1, -1};
}

static void		closest_object_light(t_vector vec_l, int type, t_rt *rt)
{
	t_root		root;
	t_obj		*tmp;

	tmp = rt->obj;
	rt->math->closest_obj_2 = NULL;
	if (type == Directional)
		rt->math->closest_t_2 = MAX;
	else
		rt->math->closest_t_2 = 1;
	while (tmp)
	{
		root = hit_obj(vec_l, rt->math->point, tmp);
		if (root.a > MIN && root.a < MAX && root.a < rt->math->closest_t_2)
		{
			rt->math->closest_t_2 = root.a;
			rt->math->closest_obj_2 = tmp;
		}
		if (root.b > MIN && root.b < MAX && root.b < rt->math->closest_t_2)
		{
			rt->math->closest_t_2 = root.b;
			rt->math->closest_obj_2 = tmp;
		}
		tmp = tmp->next;
	}
}

static void		point_direct_light_math(double *intensive, t_lights *tmp,
                                           t_vector view, t_rt *rt)
{
	double		r_dot_v;
	double		n_dot_l;
	t_vector	vec_l;
	t_vector	vec_r;

	if (tmp->type == Point)
		vec_l = ft_vec_subtract(tmp->point, rt->math->point);
	else
		vec_l = tmp->point;
	closest_object_light(vec_l, tmp->type, rt);
	if (rt->math->closest_obj_2)
		return ;
	n_dot_l = ft_vec_dot(rt->math->normal, vec_l);
	if (n_dot_l > 0)
		*intensive += tmp->intensive * n_dot_l
		              / (ft_vec_length(rt->math->normal) * ft_vec_length(vec_l));
	if (rt->math->closest_obj->specular != -1)
	{
		vec_r = ft_vec_subtract(ft_vec_multiplication_num(rt->math->normal, 2
		                                                                    * ft_vec_dot(rt->math->normal, vec_l)), vec_l);
		r_dot_v = ft_vec_dot(vec_r, view);
		if (r_dot_v > 0)
			*intensive += tmp->intensive * pow(r_dot_v / (ft_vec_length(vec_r)
			                                              * ft_vec_length(view)), rt->math->closest_obj->specular);
	}
}

double			compute_light(t_vector view, t_rt *rt)
{
	t_lights	*tmp;
	double		intensive;

	intensive = 0;
	tmp = rt->light;
	while (tmp)
	{
		if (tmp->type == Ambient)
			intensive += tmp->intensive;
		else
			point_direct_light_math(&intensive, tmp, view, rt);
		tmp = tmp->next;
	}
	intensive > 1.0 ? intensive = 1.0f : 0;
	return (intensive);
}

int				ray_trace(t_rt *rt)
{
	closest_object(rt);
	if (rt->math->closest_t == MAX || !rt->math->closest_obj)
		return (0);
	rt->math->point = ft_vec_sum(rt->camera,
	                             ft_vec_multiplication_num(rt->math->dir, rt->math->closest_t));
	rt->math->normal = get_normal(rt->math->closest_obj, rt->math->point);
	return (color_parse(rt));
}

void			render(t_rt *rt)
{
	t_img		img;
	int			color;

	img.curnt_y = -(rt->sdl->sur->h >> 1) - 1;
	img.finish_y = rt->sdl->sur->h >> 1;
	img.half_width = rt->sdl->sur->w >> 1;
	img.half_height = rt->sdl->sur->h >> 1;
	while (++img.curnt_y < img.finish_y)
	{
		img.curnt_x = -(rt->sdl->sur->w >> 1) - 1;
		img.finish_x = (rt->sdl->sur->w >> 1);
		while (++img.curnt_x < img.finish_x)
		{
			rt->math->dir = calculate_direction(img.curnt_x, img.curnt_y,
			                                    rt->sdl->sur->w, rt->sdl->sur->h);
			color = ray_trace(rt);
			put_pixel(img.curnt_x + img.half_width,
			          img.curnt_y + img.half_height, color, rt->sdl->sur);
		}
	}
}