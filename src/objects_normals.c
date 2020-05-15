/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_normals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:35:10 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 08:36:24 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_point3d		cone_normal(t_object *obj, t_point3d point)
{
	t_point3d	normal;
	double		m;
	double		k;

	k = (1 + obj->radius * obj->radius);
	m = ft_vec_dot(ft_vec_subtract(point, obj->pos), obj->direction);
	normal = ft_vec_multiplication_num((obj->direction), (float)(m * k));
	normal = ft_vec_subtract(ft_vec_subtract(point, obj->pos), normal);
	normal = ft_vec_normalize(normal);
	return (normal);
}

t_point3d		cylinder_normal(t_object *obj, t_point3d point)
{
	t_point3d	normal;
	double		m;

	m = ft_vec_dot(ft_vec_subtract(point, obj->pos), obj->direction);
	obj->direction = ft_vec_normalize(obj->direction);
	normal = ft_vec_multiplication_num(obj->direction, m);
	normal = ft_vec_subtract(ft_vec_subtract(point, obj->pos), normal);
	normal = ft_vec_normalize(normal);
	return (normal);
}

t_point3d		sphere_normal(t_object *obj, t_point3d point)
{
	t_point3d	normal;

	normal = ft_vec_subtract(point, obj->pos);
	normal = ft_vec_normalize(normal);
	return (normal);
}

t_point3d		plane_normal(t_object *obj, t_point3d point)
{
	t_point3d	normal;

	(void)point;
	if (!(obj->direction.x) && !(obj->direction.y) && !(obj->direction.z))
		normal = (t_point3d){0, 0, 1};
	normal = ft_vec_normalize(obj->direction);
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
