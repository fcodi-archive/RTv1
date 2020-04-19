#ifndef FT_SDL_H
# define FT_SDL_H

# include <math.h>
# include <SDL.h>
# include <libft.h>

typedef struct				s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*sur;
	SDL_Event		event;
}							t_sdl;

#endif
