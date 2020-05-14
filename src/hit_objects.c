/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:37:10 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/14 04:45:29 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_root			hit_cone(t_point3d dir, t_point3d campos, t_object *cone)
{
	t_point3d	res;
	float		discrim;
	t_root		root;
	float		k;

	cone->direction = ft_vec_normalize(cone->direction);
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

	cylinder->direction = ft_vec_normalize(cylinder->direction);
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
	plane->direction = ft_vec_normalize(plane->direction);
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
