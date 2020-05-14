/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_manager_checklist.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:01:51 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 09:01:52 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RTv1.h>

void	init_checklist(t_scene_manager *manager)
{
	int		i;

	if (!manager)
		return ;
	i = 0;
	while (i < FIELD_OPTION_COUNT)
		manager->checklist[i++] = FALSE;
}

_Bool	is_valid_object_checklist(t_scene_manager *manager)
{
	if (manager && manager->checklist[type] && manager->checklist[color]
		&& manager->checklist[specular] && manager->checklist[pos]
		&& manager->checklist[radius] && manager->checklist[direction])
		return (TRUE);
	return (FALSE);
}

_Bool	is_valid_light_checklist(t_scene_manager *manager)
{
	if (manager && manager->checklist[type] && manager->checklist[intensive]
		&& manager->checklist[pos])
		return (TRUE);
	return (FALSE);
}

_Bool	is_valid_camera_checklist(t_scene_manager *manager)
{
	if (manager && manager->checklist[pos] && manager->checklist[direction])
		return (TRUE);
	return (FALSE);
}

_Bool	is_valid_checklist(t_scene_manager *manager)
{
	_Bool	result;

	result = FALSE;
	if (!manager)
		return (result);
	if (manager->field == camera)
		result = is_valid_camera_checklist(manager);
	if (manager->field == object)
		result = is_valid_object_checklist(manager);
	if (manager->field == light)
		result = is_valid_light_checklist(manager);
	init_checklist(manager);
	return (result);
}
