/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:03:01 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 09:06:32 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		destroy_scene(t_scene *scene)
{
	size_t		i;

	if (!scene)
		return ;
	i = 0;
	if (scene->object)
	{
		while (scene->object[i])
			free(scene->object[i++]);
		free(scene->object);
	}
	i = 0;
	if (scene->light)
	{
		while (scene->light[i])
			free(scene->light[i++]);
		free(scene->light);
	}
	free(scene);
}

t_scene		*new_scene(void)
{
	t_scene		*scene;

	if (!(scene = (t_scene *)ft_memalloc(sizeof(t_scene))))
		return (NULL);
	init_camera(&scene->camera);
	return (scene);
}
