/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:57:12 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 08:57:14 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_scene		*init_scene(const char *path)
{
	t_scene_manager		*manager;
	t_scene				*scene;
	int					result;

	if (!path || !(manager = new_scene_manager(path)))
		return (NULL);
	while ((result = get_next_line(manager->fd, &manager->line)) > 0)
	{
		manager->field = parse_field(manager->line);
		ft_strdel(&manager->line);
		if ((result = manager->field == wrong_field ? ERROR : result) == ERROR
			|| ((result = manager->was_camera && manager->field == camera ?
					ERROR : result) == ERROR)
			|| (manager->field == separator)
			|| !(set_current_parse_element(manager, TRUE))
			|| (result = parse_scene(manager) ? 0 : ERROR) == ERROR
			|| !(set_current_parse_element(manager, FALSE)))
			break ;
		manager->field == camera
		? (manager->was_camera = TRUE) : FALSE;
	}
	result = manager->was_camera ? result : ERROR;
	!result ? result = !set_current_parse_element(manager, FALSE) : FALSE;
	scene = destroy_scene_manager(manager, result == 0 ? FALSE : TRUE);
	return (scene);
}
