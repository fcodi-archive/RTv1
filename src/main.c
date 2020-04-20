#include <RTv1.h>

int		main(int ac, char **av)
{
	t_scene		*scene;
	t_sdl		*sdl;

	if (ac == 2)
	{
		if (!(scene = init_scene(av[1])))
			return (EXIT_FAILURE);
		sdl = init_sdl();
		loop_sdl(sdl);
		destroy_scene(scene);
	}
	ft_exit(rc_ok, EXIT_MESSAGE);
}