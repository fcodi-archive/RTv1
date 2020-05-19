/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:53:38 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 08:55:55 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_vec_distance(t_point3d a, t_point3d b)
{
	double	distance;

	distance = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)
	+ (a.z - b.z) * (a.z - b.z));
	return (distance);
}

double	ft_vec_dot(t_point3d a, t_point3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	ft_vec_length(t_point3d a)
{
	double	len;

	len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	return (len);
}

double	ft_vec_multiplication(t_point3d a, t_point3d b, double angle)
{
	double	result;
	double	len_a;
	double	len_b;

	len_a = ft_vec_length(a);
	len_b = ft_vec_length(b);
	result = len_a * len_b * cos(angle);
	return (result);
}
