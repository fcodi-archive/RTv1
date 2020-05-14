/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:55:08 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 08:55:09 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <point3d.h>

void		init_point3d(t_point3d *point)
{
	if (!point)
		return ;
	point->x = 0.0;
	point->y = 0.0;
	point->z = 0.0;
}

t_point3d	ft_vec_multiplication_num(t_point3d a, double num)
{
    t_point3d	b;

    b.x = a.x * num;
    b.y = a.y * num;
    b.z = a.z * num;
    return (b);
}

t_point3d	ft_vec_subtract(t_point3d a, t_point3d b)
{
    t_point3d	c;

    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return (c);
}

t_point3d	ft_vec_sum(t_point3d a, t_point3d b)
{
    t_point3d	c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return (c);
}

t_point3d 	ft_vec_cross(t_point3d a, t_point3d b)
{
	t_point3d	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}
