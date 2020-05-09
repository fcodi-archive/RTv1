#include <point3d.h>
#include <RTv1.h>

t_point3d		rotate(t_point3d axis, t_point3d vector, double angle)
{
	t_point3d	res;
	double		sin_a;
	double		cos_a;

	sin_a = sin(angle);
	cos_a = cos(angle);
	res.x = (cos_a + (1 - cos_a) * axis.x * axis.x) * vector.x +
			((1 - cos_a) * axis.x * axis.y - sin_a * axis.z) * vector.y +
			((1 - cos_a) * axis.x * axis.z + sin_a * axis.y) * vector.z;
	res.y = ((1 - cos_a) * axis.y * axis.x + sin_a * axis.z) * vector.x +
			(cos_a + (1 - cos_a) * axis.y * axis.y) * vector.y +
			((1 - cos_a) * axis.z * axis.y - sin_a * axis.x) * vector.z;
	res.z = ((1 - cos_a) * axis.z * axis.x - sin_a * axis.y) * vector.x +
			((1 - cos_a) * axis.z * axis.y + sin_a * axis.x) * vector.y +
			(cos_a + (1 - cos_a) * axis.z * axis.z) * vector.z;
	return (res);
}

t_point3d		find_direction(t_camera *camera, int x, int y, t_img *img)
{
	t_point3d	res;

	res = ft_vec_sum(
			ft_vec_sum(ft_vec_multiplication_num(img->border_x, (WIDTH / 2 - (double)x) / WIDTH),
					 ft_vec_multiplication_num(img->border_y, (HEIGHT / 2 - (double)y) / HEIGHT)),
			camera->direction);
	res = ft_vec_multiplication_num(res, (double)1.0 / ft_vec_length(res));
	return (res);
}

void			define_screen(t_img *img, t_camera *camera)
{
	img->left = rotate(camera->norm, camera->direction, FOV / 2);
	img->right = rotate(camera->norm, camera->direction, -(FOV / 2));
	img->up = rotate(ft_vec_cross(camera->direction, camera->norm),
						camera->direction, (FOV / 2));
	img->down = rotate(ft_vec_cross(camera->direction, camera->norm),
						  camera->direction, -(FOV / 2));
	img->border_x = ft_vec_subtract(img->right, img->left);
	img->border_y = ft_vec_subtract(img->up, img->down);
}


t_point3d		cone_normal(t_object *obj, t_point3d point)
{
	t_point3d	normal;
	double		m;
	double		k;

	k = (1 + obj->radius * obj->radius);
	m = ft_vec_dot(ft_vec_subtract(point, obj->pos), obj->direction);
	normal = ft_vec_multiplication_num((obj->direction), (float)(m * k));
	normal = ft_vec_subtract(ft_vec_subtract(point, obj->pos), normal);
	normal = ft_vec_multiplication_num(normal,
	                                   (double)(1.f / ft_vec_length(normal)));
	return (normal);
}

t_point3d		cylinder_normal(t_object *obj, t_point3d point)
{
	t_point3d	normal;
	double		m;

	m = ft_vec_dot(ft_vec_subtract(point, obj->pos), obj->direction);
	obj->direction = ft_vec_multiplication_num(obj->direction,
	                                     (double)(1.f / ft_vec_length(obj->direction)));
	normal = ft_vec_multiplication_num(obj->direction, m);
	normal = ft_vec_subtract(ft_vec_subtract(point, obj->pos), normal);
	normal = ft_vec_multiplication_num(normal,
	                                   (double)(1.f / ft_vec_length(normal)));
	return (normal);
}

t_point3d		sphere_normal(t_object *obj, t_point3d point)
{
	t_point3d	normal;

	normal = ft_vec_subtract(point, obj->pos);
	normal = ft_vec_multiplication_num(normal,
	                                   (double)(1.f / ft_vec_length(normal)));
	return (normal);
}

t_point3d		plane_normal(t_object *obj, t_point3d point)
{
	t_point3d	normal;

	normal = obj->direction;
	return (normal);
}

t_point3d		get_normal(t_object *obj, t_point3d point)
{
	if (obj->type == cone)
		return (cone_normal(obj, point));
	if (obj->type == cylinder)
		return (cylinder_normal(obj, point));
	if (obj->type == sphere)
		return (sphere_normal(obj, point));
	if (obj->type == plane)
		return (plane_normal(obj, point));
	return ((t_point3d){0, 0, 0});
}

void			closest_object(t_scene *scene)
{
	t_root		root;
	int         i;

	i = 0;
	scene->math->closest_obj = NULL;
	scene->math->closest_t = MAX;
	while (scene->object[i])
	{
		root = hit_obj(scene->math->dir, scene->camera.pos, scene->object[i]);
		if (root.a > MIN && root.a < MAX && root.a < scene->math->closest_t)
		{
			scene->math->closest_t = root.a;
			scene->math->closest_obj = scene->object[i];
		}
		if (root.b > MIN && root.b < MAX && root.b < scene->math->closest_t)
		{
			scene->math->closest_t = root.b;
			scene->math->closest_obj = scene->object[i];
		}
		i++;
	}
}

t_root			hit_cone(t_point3d dir, t_point3d campos, t_object *cone)
{
	t_point3d	res;
	float		discrim;
	t_root		root;
	float		k;

	k = 1 + cone->radius * cone->radius;
	res.x = ft_vec_dot(dir, dir) - k * pow(ft_vec_dot(dir, cone->direction), 2.0);
	res.y = 2 * (ft_vec_dot(dir, ft_vec_subtract(campos, cone->pos)) -
	             k * ft_vec_dot(dir, cone->direction) *
	             ft_vec_dot(ft_vec_subtract(campos, cone->pos), cone->direction));
	res.z = ft_vec_dot(ft_vec_subtract(campos, cone->pos),
	                   ft_vec_subtract(campos, cone->pos)) - k
	                                                         * pow(ft_vec_dot(ft_vec_subtract(campos, cone->pos),
	                                                                          cone->direction), 2);
	discrim = res.y * res.y - (4.0f * res.x * res.z);
	if (discrim < 0)
		return (t_root){-1, -1};
	root.a = ((-res.y + sqrtf(discrim)) / (2.0 * res.x));
	root.b = ((-res.y - sqrtf(discrim)) / (2.0 * res.x));
	return (root);
}

t_root			hit_cylinder(t_point3d dir, t_point3d campos, t_object *cylinder)
{
	t_point3d	res;
	double		discrim;
	t_root		root;

	res.x = ft_vec_dot(dir, dir) - pow(ft_vec_dot(dir, cylinder->direction), 2.0);
	res.y = (ft_vec_dot(dir, ft_vec_subtract(campos, cylinder->pos))
	         - ft_vec_dot(dir, cylinder->direction)
	           * ft_vec_dot(ft_vec_subtract(campos, cylinder->pos),
	                        cylinder->direction)) * 2.0;
	res.z = ft_vec_dot(ft_vec_subtract(campos, cylinder->pos),
	                   ft_vec_subtract(campos, cylinder->pos))
	        - pow(ft_vec_dot(ft_vec_subtract(campos, cylinder->pos),
	                         cylinder->direction), 2)
	        - (cylinder->radius * cylinder->radius);
	discrim = res.y * res.y - (4.0 * res.x * res.z);
	if (discrim < 0)
		return (t_root){-1, -1};
	root.a = ((-res.y + sqrt(discrim)) / (2.0 * res.x));
	root.b = ((-res.y - sqrt(discrim)) / (2.0 * res.x));
	return (root);
}

t_root			hit_sphere(t_point3d dir, t_point3d campos, t_object *sphere)
{
	t_root		root;
	t_point3d	oc;
	t_point3d	res;
	double		discrim;

	oc = ft_vec_subtract(campos, sphere->pos);
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

t_root			hit_plane(t_point3d dir, t_point3d campos, t_object *plane)
{
	t_root		root;

	root = (t_root){-1, -1};
	if (plane->direction.x != 0
	    || plane->direction.y != 0
	    || plane->direction.z != 0)
		root.a = ft_vec_dot(plane->direction,
		                    ft_vec_subtract(plane->pos, campos))
		         / ft_vec_dot(plane->direction, dir);
	root.b = -1.0;
	return (root);
}

t_root			hit_obj(t_point3d dir, t_point3d campos, t_object *obj)
{
	if (obj->type == sphere)
		return (hit_sphere(dir, campos, obj));
	else if (obj->type == plane)
		return (hit_plane(dir, campos, obj));
	else if (obj->type == cone)
		return (hit_cone(dir, campos, obj));
	else if (obj->type == cylinder)
		return (hit_cylinder(dir, campos, obj));
	return (t_root){-1, -1};
}

int				set_color_rgb(int red, int green, int blue)
{
	return ((red & 0xFF) << 16) + ((green & 0xFF) << 8) + (blue & 0xFF);
}

int				color_parse(t_scene *scene)
{
	t_point3d	rgb;
	t_point3d   col;

	col.x = (int)scene->math->closest_obj->color.r;
	col.y = (int)scene->math->closest_obj->color.g;
	col.z = (int)scene->math->closest_obj->color.b;
	rgb = ft_vec_multiplication_num(col,
	                                compute_light(ft_vec_multiplication_num(scene->math->dir, -1), scene));
	if (rgb.x > 255)
		rgb.x = 255;
	if (rgb.y > 255)
		rgb.y = 255;
	if (rgb.z > 255)
		rgb.z = 255;
	return (set_color_rgb((int)rgb.x, (int)rgb.y, (int)rgb.z));
}

int				ray_trace(t_scene *scene)
{
	closest_object(scene);
	if (scene->math->closest_t == MAX || !scene->math->closest_obj)
		return (0);
	scene->math->point = ft_vec_sum(scene->camera.pos,
	                             ft_vec_multiplication_num(scene->math->dir, scene->math->closest_t));
	scene->math->normal = get_normal(scene->math->closest_obj, scene->math->point);
	return (color_parse(scene));
}

void 			change_view(t_camera *cam)
{
	double 		angle_x;
	double 		angle_y;
	t_point3d	axis;

	angle_x = 0;//M_PI / 6;
	angle_y = 0;//M_PI / 6;
	axis = (t_point3d){0, 1 ,0};
	//axis = ft_vec_cross(cam->direction, cam->norm);
	if (angle_x)
	{
		cam->direction = rotate(axis, cam->direction, angle_x);
		cam->norm = rotate(axis, cam->norm, angle_x);
	}
	if (angle_y)
	{
		axis = ft_vec_cross(cam->direction, cam->norm);
		cam->direction = rotate(axis, cam->direction, angle_y);
		cam->norm = rotate(axis, cam->norm, angle_y);
	}
}

void			render(t_scene *scene)
{
	t_img		img;
	int			color;

	int x = -1;
	int y;
	scene->camera.norm = (t_point3d){0, 1, 0};
	change_view(&(scene->camera));
	define_screen(&img, &(scene->camera));
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			scene->math->dir = find_direction(&(scene->camera), x, y, &img);
			color = ray_trace(scene);
			put_pixel(x,y, color, scene->sdl->sur);
		}
	}
}