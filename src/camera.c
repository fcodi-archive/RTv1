/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:49:45 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 20:46:05 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RTv1.h>

void			init_camera(t_camera *camera)
{
	if (!camera)
		return ;
	init_point3d(&camera->pos);
	init_point3d(&camera->direction);
	camera->norm = (t_point3d){0, 1, 0};
}

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
