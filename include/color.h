/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:48:51 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/14 04:04:11 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLOR_H
# define FT_COLOR_H

# include "ft_bool.h"

# ifndef T_COLOR
#  define T_COLOR

typedef union			u_color
{
	int					color;
	struct
	{
		uint8_t			b: 8;
		uint8_t			g: 8;
		uint8_t			r: 8;
		uint8_t			a: 8;
	};
}						t_color;
# endif

void	init_color(t_color *color);
_Bool	is_valid_color_byte(intmax_t integer);

#endif
