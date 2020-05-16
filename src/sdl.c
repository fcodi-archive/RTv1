/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:03:27 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/15 11:33:46 by owl              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sdl.h>

void			init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit(EXIT_FAILURE);
	if (!(sdl->win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		exit(EXIT_FAILURE);
	if (!(sdl->sur = SDL_GetWindowSurface(sdl->win)))
		exit(EXIT_FAILURE);
}

void			put_pixel(int x, int y, int color, SDL_Surface *sur)
{
	int			*pixels;

	pixels = (int *)sur->pixels;
	pixels[sur->w * y + x] = color;
}

void			sdl_loop(SDL_Window *win)
{
	SDL_Event		event;

	SDL_UpdateWindowSurface(win);
	while (true)
	{
		SDL_WaitEvent(&event);
		if (SDL_QUIT == event.type)
			break ;
		if (event.type == SDL_KEYDOWN)
			if (SDLK_ESCAPE == event.key.keysym.sym)
				break ;
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
}
