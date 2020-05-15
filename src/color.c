/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:41:24 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 08:41:59 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_color(t_color *color)
{
	if (!color)
		return ;
	color->color = 0;
}

_Bool	is_valid_color_byte(intmax_t integer)
{
	const uint8_t	byte = (uint8_t)integer;

	return (byte == integer ? TRUE : FALSE);
}

int		set_color_rgb(int red, int green, int blue)
{
	return ((red & 0xFF) << 16) + ((green & 0xFF) << 8) + (blue & 0xFF);
}

int		color_parse(t_scene *scene)
{
	t_point3d	rgb;
	t_point3d	col;

	col.x = (int)scene->math->closest_obj->color.r;
	col.y = (int)scene->math->closest_obj->color.g;
	col.z = (int)scene->math->closest_obj->color.b;
	rgb = ft_vec_multiplication_num(col,
			compute_light(
					ft_vec_multiplication_num(scene->math->dir, -1), scene));
	if (rgb.x > 255)
		rgb.x = 255;
	if (rgb.y > 255)
		rgb.y = 255;
	if (rgb.z > 255)
		rgb.z = 255;
	return (set_color_rgb((int)rgb.x, (int)rgb.y, (int)rgb.z));
}
