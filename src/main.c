/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:57:55 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/18 08:34:16 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static void		show_usage(int code)
{
	if (!code)
		ft_putendl("Usage: ./RTv1 file.rtv");
	else if (code == 1)
		ft_putendl("Can't open file or it dosn't exists!");
	else if (code == 2)
		ft_putendl("Invalid config file or not file at all");
	exit(EXIT_FAILURE);
}

static _Bool	check_file_exist(const char *path)
{
	const int		fd = open(path, O_RDONLY);
	const _Bool		result = fd == ERROR ? FALSE : TRUE;

	fd == ERROR ? TRUE : close(fd);
	return (result);
}

int				main(int ac, char **av)
{
	t_scene		*scene;

	if (ac == 2)
	{
		if (!check_file_exist(av[1]))
			show_usage(1);
		if (!(scene = init_scene(av[1])))
			show_usage(2);
		scene->sdl = (t_sdl *)ft_malloc(sizeof(t_sdl));
		init_sdl(scene->sdl);
		scene->math = (t_math *)ft_malloc(sizeof(t_math));
		scene->math->closest_obj = (t_object *)ft_malloc(sizeof(t_object));
		render(scene);
		sdl_loop(scene->sdl->win);
		destroy_scene(scene);
		SDL_Quit();
		ft_exit(rc_ok, EXIT_MESSAGE);
	}
	show_usage(0);
}
