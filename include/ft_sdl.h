/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_SDL.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:49:28 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/18 08:25:00 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SDL_H
# define FT_SDL_H

# include <math.h>
# include <SDL.h>
# include "libft.h"
# include "color.h"
# include <stdbool.h>

# define WINDOW_MODE_DEFAULT SDL_WINDOW_SHOWN
# ifdef PROJECT_NAME
#  define WINDOW_TITLE_DEFAULT PROJECT_NAME
# else
#  define WINDOW_TITLE_DEFAULT "title"
# endif
# define WINDOW_WIDTH_DEFAULT 600
# define WINDOW_HEIGHT_DEFAULT 600
# define WIDTH 700
# define HEIGHT 700

typedef struct			s_sdl_attr
{
	SDL_WindowFlags		winmode;
	int					width;
	int					height;
	char				*title;
	int					win_position_x;
	int					win_position_y;
}						t_sdl_attr;

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Surface			*sur;
	SDL_Event			event;
}						t_sdl;

void					init_sdl(t_sdl *sdl);
void					put_pixel(int x, int y, int color, SDL_Surface *sur);
void					sdl_loop(SDL_Window *win);

#endif
