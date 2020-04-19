#include <ft_SDL.h>

void		ft_exit(char *error_text)
{
	ft_putstr("!");
	ft_putendl(error_text);
	ft_putstr("!");
	exit(1);
}

void			init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_exit("SDL_Init");
	if (!(sdl->win = SDL_CreateWindow("RT",
									  SDL_WINDOWPOS_UNDEFINED,
									  SDL_WINDOWPOS_UNDEFINED,
									  100, 100,
									  SDL_WINDOW_SHOWN)))
		ft_exit("SDL_CreateWindow");
	if (!(sdl->sur = SDL_GetWindowSurface(sdl->win)))
		ft_exit("SDL_GetWindowSurface");
}

void				sdl_loop(SDL_Window *win)
{
	SDL_Event		event;

	while (1)
	{
		SDL_WaitEvent(&event);
		if (SDL_QUIT == event.type || SDLK_ESCAPE == event.key.keysym.sym)
			break ;
		SDL_UpdateWindowSurface(win);
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void	sdl_run(void)
{
	t_sdl 	*sdl;

	sdl = (t_sdl*)malloc(sizeof(t_sdl));
	init_sdl(sdl);
	sdl_loop(sdl->win);
}