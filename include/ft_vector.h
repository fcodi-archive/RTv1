/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:50:16 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/14 03:34:10 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include "libft.h"

double		ft_vec_distance(t_point3d a, t_point3d b);
double		ft_vec_dot(t_point3d a, t_point3d b);
void		ft_vec_init(t_point3d a);
double		ft_vec_length(t_point3d a);
double		ft_vec_multiplication(t_point3d a, t_point3d b, double angle);
t_point3d	ft_vec_multiplication_num(t_point3d a, double num);
t_point3d	ft_vec_subtract(t_point3d a, t_point3d b);
t_point3d	ft_vec_sum(t_point3d a, t_point3d b);
t_point3d	ft_vec_cross(t_point3d a, t_point3d b);
t_point3d	ft_vec_normalize(t_point3d vec);

#endif
