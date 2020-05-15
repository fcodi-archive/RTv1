/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:42:56 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/14 04:26:55 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_point3d	ft_vec_normalize(t_point3d vec)
{
	return (ft_vec_multiplication_num(vec, (double)1.0 / ft_vec_length(vec)));
}

void		closest_object(t_scene *scene)
{
	t_root	root;
	int		i;

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

int			ray_trace(t_scene *scene)
{
	closest_object(scene);
	if (scene->math->closest_t == MAX || !scene->math->closest_obj)
		return (0);
	scene->math->point = ft_vec_sum(scene->camera.pos,
			ft_vec_multiplication_num(scene->math->dir,
					scene->math->closest_t));
	scene->math->normal = get_normal(scene->math->closest_obj,
			scene->math->point);
	return (color_parse(scene));
}

void		change_view(t_camera *cam)
{
	double		angle_x;
	double		angle_y;
	t_point3d	axis;

	angle_x = 0;
	angle_y = 0;
	axis = (t_point3d){0, 1, 0};
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

void		render(t_scene *scene)
{
	t_img		img;
	int			color;
	int			x;
	int			y;

	x = -1;
	scene->camera.direction = ft_vec_normalize(scene->camera.direction);
	scene->camera.norm = ft_vec_normalize(scene->camera.norm);
	define_screen(&img, &(scene->camera));
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			scene->math->dir = find_direction(&(scene->camera), x, y, &img);
			color = ray_trace(scene);
			put_pixel(x, y, color, scene->sdl->sur);
		}
	}
}
