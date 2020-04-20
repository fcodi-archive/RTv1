#ifndef FT_SDL_H
# define FT_SDL_H

# include <math.h>
# include <SDL2/SDL.h>
# include <libft.h>

# define WINDOW_MODE_DEFAULT SDL_WINDOW_SHOWN
# ifdef PROJECT_NAME
#  define WINDOW_TITLE_DEFAULT PROJECT_NAME
# else
#  define WINDOW_TITLE_DEFAULT "title"
# endif
# define WINDOW_WIDTH_DEFAULT 640
# define WINDOW_HEIGHT_DEFAULT 480

typedef struct		s_sdl_attr
{
	SDL_WindowFlags		winmode;
	int					width;
	int					height;
	char				*title;
	int					win_position_x;
	int					win_position_y;
}					t_sdl_attr;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*surface;
	SDL_Event		*event;
	SDL_Renderer	*renderer;
}					t_sdl;

void	loop_sdl(t_sdl *sdl);
t_sdl	*init_sdl(void);

#endif
