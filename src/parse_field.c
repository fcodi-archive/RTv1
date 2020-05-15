/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:59:58 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 20:28:53 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_field			parse_field(const char *string)
{
	if (string)
	{
		if (!*string)
			return (separator);
		if (!ft_strcmp(string, FIELD_OBJECT))
			return (object);
		if (!ft_strcmp(string, FIELD_LIGHT))
			return (light);
		if (!ft_strcmp(string, FIELD_CAMERA))
			return (camera);
	}
	return (wrong_field);
}

t_field_option	parse_field_option(const char *string)
{
	if (string)
	{
		if (!*string)
			return (option_separator);
		if (!ft_strcmp(string, FIELD_POS))
			return (pos);
		if (!ft_strcmp(string, FIELD_DIRECTION))
			return (direction);
		if (!ft_strcmp(string, FIELD_NORM))
			return (norm);
		if (!ft_strcmp(string, FIELD_INTENSIVE))
			return (intensive);
		if (!ft_strcmp(string, FIELD_RADIUS))
			return (radius);
		if (!ft_strcmp(string, FIELD_SPECULAR))
			return (specular);
		if (!ft_strcmp(string, FIELD_COLOR))
			return (color);
		if (!ft_strcmp(string, FIELD_TYPE))
			return (type);
	}
	return (wrong_option_field);
}
