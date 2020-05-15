/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:59:29 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 08:59:34 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

_Bool	parse_color_current(t_color *color, char **numbers)
{
	intmax_t	integer[COLOR_COUNT];
	int			i;

	if (!color || !numbers || !*numbers)
		return (FALSE);
	i = -1;
	while (++i < COLOR_COUNT)
		if (!is_valid_color_byte(
				(integer[i] = ft_atoll_base(numbers[i], 10))))
			return (FALSE);
	color->r = integer[0];
	color->g = integer[1];
	color->b = integer[2];
	return (TRUE);
}

_Bool	parse_color(t_scene_manager *manager)
{
	char	**integers;
	_Bool	result;

	if (!manager)
		return (FALSE);
	if (get_string_array_size(manager->parts) != 4
		|| !(integers = parse_integers(manager->line)))
		return (FALSE);
	if ((result = get_string_array_size(integers) == 3 ? TRUE : FALSE))
		result = parse_color_current(&manager->object->color, integers);
	ft_astr_del(integers);
	return (result);
}
