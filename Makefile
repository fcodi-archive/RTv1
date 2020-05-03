# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/01 10:42:59 by fcodi             #+#    #+#              #
#    Updated: 2020/05/01 19:00:45 by fcodi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SOURCE_FILES = camera.c \
	color.c \
	init_scene.c \
	set_current_parse_element.c \
	scene.c \
	parse_field.c \
	point3d.c \
	scene_manager.c \
	main.c \
	SDL.c \
	raytracer.c \
	parse_point3d.c \
	parse_type.c \
	parse_color.c \
	parse_scene.c \
	scene_manager_checklist.c \
	light.c \
	parse_double.c \
	ft_vector.c \
	object.c \
	parse_option.c

INCLUDE_FILES = color.h \
	ft_vector.h \
	RTv1.h \
	ft_SDL.h \
	point3d.h \
	render.h

include libft/mk/project.mk

# **************************************************************************** #
#	Rules
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBSDL2)
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)

clean:
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)

fclean:
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)

re: $(LIBSDL2)
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)