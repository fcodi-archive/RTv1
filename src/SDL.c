#include <ft_SDL.h>

void			init_sdl(t_sdl *sdl)
{
/*	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit(EXIT_FAILURE);//ft_exit("SDL_Init");*/
	if (!(sdl->win = SDL_CreateWindow("RTv1",
	                                  SDL_WINDOWPOS_UNDEFINED,
	                                  SDL_WINDOWPOS_UNDEFINED,
	                                  WIDTH, HEIGHT,
	                                  SDL_WINDOW_SHOWN)))
		exit(EXIT_FAILURE);//ft_exit("SDL_CreateWindow");
	if (!(sdl->sur = SDL_GetWindowSurface(sdl->win)))
		exit(EXIT_FAILURE);//ft_exit("SDL_GetWindowSurface");
}

void			put_pixel(int x, int y, int color, SDL_Surface *sur)
{
	int			*pixels;

	pixels = (int *)sur->pixels;
	pixels[sur->w * y + x] = color;
}

void            draw_something(t_sdl *sdl)
{
	int     x;
	int     y;
	int     color;

	color = 0;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			put_pixel(x, y, color, sdl->sur);
			//color += 1000;
		}
		color += 1;
	}
}

void				sdl_loop(SDL_Window *win)
{
	SDL_Event		event;

	while (TRUE)
	{
		SDL_WaitEvent(&event);
		if (SDL_QUIT == event.type || SDLK_ESCAPE == event.key.keysym.sym)
			break ;
		SDL_UpdateWindowSurface(win);
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
}
//void	destroy_sdl(t_sdl *sdl)
//{
//	sdl->renderer ? SDL_DestroyRenderer(sdl->renderer) : FALSE;
//	sdl->surface ? SDL_FreeSurface(sdl->surface) : FALSE;
//	sdl->win ? SDL_DestroyWindow(sdl->win) : FALSE;
//	SDL_Quit();
//}
//
//void	putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
//{
//	const int	bpp = surface->format->BytesPerPixel;
//	Uint8 *p;
//
//
//	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
//	if (bpp == 1)
//		*p = pixel;
//	if (bpp == 2)
//		*(Uint16 *)p = pixel;
//	if (bpp == 3)
//	{
//		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
//		{
//			p[0] = (pixel >> 16) & 0xff;
//			p[1] = (pixel >> 8) & 0xff;
//			p[2] = pixel & 0xff;
//		}
//		else
//		{
//			p[0] = pixel & 0xff;
//			p[1] = (pixel >> 8) & 0xff;
//			p[2] = (pixel >> 16) & 0xff;
//		}
//	}
//	if (bpp == 4)
//		*(Uint32 *)p = pixel;
//}

//void	ft_SDL_exit(t_sdl *sdl, const int code, const char *message)
//{
//	ft_putendl(SDL_GetError());
//	destroy_sdl(sdl);
//	ft_exit(code, message);
//}
//
//t_sdl 	*init_sdl_with_attr(t_sdl_attr *attr)
//{
//	t_sdl	*sdl;
//
//	if (!(sdl = (t_sdl *)ft_malloc(sizeof(t_sdl))))
//		return (NULL);
//	if (SDL_Init(SDL_INIT_VIDEO) == ERROR)
//		ft_SDL_exit(sdl, rc_initialize_fail, EXIT_MESSAGE);
//	if (!(sdl->win = SDL_CreateWindow(attr->title,
//									  attr->win_position_x, attr->win_position_y,
//									  attr->width, attr->height, attr->winmode)))
//		ft_SDL_exit(sdl, rc_initialize_fail, EXIT_MESSAGE);
//	if (!(sdl->renderer = SDL_CreateRenderer(sdl->win, 1,
//			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
//		ft_SDL_exit(sdl, rc_initialize_fail, EXIT_MESSAGE);
//	SDL_UpdateWindowSurface(sdl->win);
//	if (!(sdl->surface = SDL_GetWindowSurface(sdl->win)))
//		ft_SDL_exit(sdl, rc_initialize_fail, EXIT_MESSAGE);
//
//	return (sdl);
//}
//
//void	init_sdl_attr(t_sdl_attr *attr)
//{
//	if (!attr)
//		return ;
//	attr->winmode = WINDOW_MODE_DEFAULT;
//	attr->width = WINDOW_WIDTH_DEFAULT;
//	attr->height = WINDOW_HEIGHT_DEFAULT;
//	attr->title = WINDOW_TITLE_DEFAULT;
//}
//
//t_sdl	*init_sdl(void)
//{
//	t_sdl_attr	attr;
//
//	init_sdl_attr(&attr);
//	return (init_sdl_with_attr(&attr));
//}


//void	loop_sdl(t_sdl *sdl)
//{
//	SDL_Texture	*texture;
//	SDL_Event	event;
//	int			x;
//	int			y;
//	t_color		color;
//
//	x = 0;
//	y = 0;
//	color.b = 255;
//	//SDL_GetRenderer(sdl->win);
//	while (TRUE)
//	{
//		SDL_WaitEvent(&event);
//		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
//			break ;
//		if (x < 1366)
//			x++;
//		else
//		{
//			x = 0;
//			y++;
//		}
//		if (y > 768)
//			y = 0;
//		SDL_FreeSurface(sdl->surface);
//		putpixel(sdl->surface, x, y, color.color);
//		texture = SDL_CreateTextureFromSurface(sdl->renderer, sdl->surface);
//		SDL_RenderClear(sdl->renderer);
//		SDL_RenderCopy(sdl->renderer, texture, NULL, NULL);
//		SDL_RenderPresent(sdl->renderer);
//	}
//	SDL_DestroyTexture(texture);
//	destroy_sdl(sdl);
//}
