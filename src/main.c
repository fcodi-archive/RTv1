#include <RTv1.h>

int		main(int ac, char **av)
{
	t_scene		*scene;
	t_sdl		*sdl;

	if (ac == 2)
	{
		if (!(scene = init_scene(av[1])))
			return (EXIT_FAILURE);
		sdl = (t_sdl *)malloc(sizeof(sdl));
		init_sdl(sdl);
		draw_something(sdl);
		sdl_loop(sdl->win);
		destroy_scene(scene);
	}
	ft_exit(rc_ok, EXIT_MESSAGE);
}