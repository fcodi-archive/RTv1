/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:01:17 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 09:01:18 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

_Bool	parse_object_type(t_scene_manager *manager)
{
	if (!manager)
		return (FALSE);
	if (!ft_strcmp(manager->parts[1], OBJECT_TYPE_CYLINDER))
		manager->object->type = cylinder;
	else if (!ft_strcmp(manager->parts[1], OBJECT_TYPE_CONE))
		manager->object->type = cone;
	else if (!ft_strcmp(manager->parts[1], OBJECT_TYPE_PLANE))
		manager->object->type = plane;
	else if (!ft_strcmp(manager->parts[1], OBJECT_TYPE_SPHERE))
		manager->object->type = sphere;
	else
		return (FALSE);
	return (TRUE);
}

_Bool	parse_light_type(t_scene_manager *manager)
{
	if (!manager)
		return (FALSE);
	if (!ft_strcmp(manager->parts[1], LIGHT_TYPE_AMBIENT))
		manager->light->type = ambient;
	else if (!ft_strcmp(manager->parts[1], LIGHT_TYPE_DIRECTIONAL))
		manager->light->type = directional;
	else if (!ft_strcmp(manager->parts[1], LIGHT_TYPE_POINT))
		manager->light->type = point;
	else
		return (FALSE);
	return (TRUE);
}

_Bool	parse_type(t_scene_manager *manager)
{
	if (manager)
	{
		if (get_string_array_size(manager->parts) != 2)
			return (FALSE);
		if (manager->field == object)
			return (parse_object_type(manager));
		if (manager->field == light)
			return (parse_light_type(manager));
	}
	return (FALSE);
}
