#include <ft_SDL.h>

void	destroy_sdl(t_sdl *sdl)
{
	sdl->renderer ? SDL_DestroyRenderer(sdl->renderer) : FALSE;
	sdl->surface ? SDL_FreeSurface(sdl->surface) : FALSE;
	sdl->win ? SDL_DestroyWindow(sdl->win) : FALSE;
	SDL_Quit();
}

void	putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	const int	bpp = surface->format->BytesPerPixel;
	Uint8 *p;

	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		*p = pixel;
	if (bpp == 2)
		*(Uint16 *)p = pixel;
	if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
	}
	if (bpp == 4)
		*(Uint32 *)p = pixel;
}

void	ft_SDL_exit(t_sdl *sdl, const int code, const char *message)
{
	ft_putendl(SDL_GetError());
	destroy_sdl(sdl);
	ft_exit(code, message);
}

t_sdl 	*init_sdl_with_attr(t_sdl_attr *attr)
{
	t_sdl	*sdl;

	if (!(sdl = (t_sdl *)ft_malloc(sizeof(t_sdl))))
		return (NULL);
	if (SDL_Init(SDL_INIT_VIDEO) == ERROR)
		ft_SDL_exit(sdl, rc_initialize_fail, EXIT_MESSAGE);
	if (!(sdl->win = SDL_CreateWindow(attr->title,
									  attr->win_position_x, attr->win_position_y,
									  attr->width, attr->height, attr->winmode)))
		ft_SDL_exit(sdl, rc_initialize_fail, EXIT_MESSAGE);
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->win, 1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		ft_SDL_exit(sdl, rc_initialize_fail, EXIT_MESSAGE);
	SDL_UpdateWindowSurface(sdl->win);
	if (!(sdl->surface = SDL_GetWindowSurface(sdl->win)))
		ft_SDL_exit(sdl, rc_initialize_fail, EXIT_MESSAGE);

	return (sdl);
}

void	init_sdl_attr(t_sdl_attr *attr)
{
	if (!attr)
		return ;
	attr->winmode = WINDOW_MODE_DEFAULT;
	attr->width = WINDOW_WIDTH_DEFAULT;
	attr->height = WINDOW_HEIGHT_DEFAULT;
	attr->title = WINDOW_TITLE_DEFAULT;
}

t_sdl	*init_sdl(void)
{
	t_sdl_attr	attr;

	init_sdl_attr(&attr);
	return (init_sdl_with_attr(&attr));
}

void	loop_sdl(t_sdl *sdl)
{
	SDL_Texture	*texture;
	SDL_Event	event;
	int			x;
	int			y;
	t_color		color;

	x = 0;
	y = 0;
	color.b = 255;
	//SDL_GetRenderer(sdl->win);
	SDL_WaitEvent(&event);
	while (TRUE)
	{
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
			break ;
		if (x < 1366)
			x++;
		else
		{
			x = 0;
			y++;
		}
		if (y > 768)
			y = 0;
		SDL_FreeSurface(sdl->surface);
		putpixel(sdl->surface, x, y, color.color);
		texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->surface);
		SDL_RenderClear(sdl->renderer);
		SDL_RenderCopy(sdl->renderer, texture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);
	}
	SDL_DestroyTexture(texture);
	destroy_sdl(sdl);
}
