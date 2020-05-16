/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:48:51 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/15 11:18:30 by owl              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COLOR_H
# define FT_COLOR_H

# include "ft_bool.h"

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

void				init_color(t_color *color);
_Bool				is_valid_color_byte(intmax_t integer);

#endif
