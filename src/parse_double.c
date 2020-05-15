/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:59:44 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 08:59:46 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

_Bool	parse_double(t_scene_manager *manager)
{
	if (!manager)
		return (FALSE);
	if (get_string_array_size(manager->parts) != 2)
		return (FALSE);
	if (manager->field == object)
	{
		if (manager->option == specular
		&& isnan((manager->object->specular = ft_atod_ex(manager->parts[1]))))
			return (FALSE);
		if ((manager->option == radius
			&& isnan(manager->object->radius = ft_atod_ex(manager->parts[1])))
			|| manager->object->radius < 0)
			return (FALSE);
	}
	if (manager->field == light && manager->option == intensive
		&& isnan(manager->light->intensive = ft_atod_ex(manager->parts[1])))
		return (FALSE);
	return (TRUE);
}
