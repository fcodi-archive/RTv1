/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:57:55 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 08:57:56 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		main(int ac, char **av)
{
	t_scene		*scene;

	if (ac == 2)
	{
		if (!(scene = init_scene(av[1])))
			return (EXIT_FAILURE);
		scene->sdl = (t_sdl *)ft_malloc(sizeof(t_sdl));
		init_sdl(scene->sdl);
		scene->math = (t_math *)ft_malloc(sizeof(t_math));
		scene->math->closest_obj = (t_object *)ft_malloc(sizeof(t_object));
		render(scene);
		sdl_loop(scene->sdl->win);
		destroy_scene(scene);
		SDL_Quit();
	}
	ft_exit(rc_ok, EXIT_MESSAGE);
}
