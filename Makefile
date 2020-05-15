# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/01 10:42:59 by fcodi             #+#    #+#              #
#    Updated: 2020/05/14 05:47:12 by fcodi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

NAME := RTv1

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
	parse_option.c \
	objects_normals.c \
	hit_objects.c \

INCLUDE_FILES = color.h \
	ft_vector.h \
	RTv1.h \
	ft_SDL.h \
	point3d.h \

include libft/mk/project.mk
include $(SDL2_MK)
include $(LIB_MK)

# **************************************************************************** #
#	Rules
# **************************************************************************** #

.PHONY: $(NAME)

all: $(NAME)

$(NAME): sdl2 $(LIBFT)
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)

$(LIBFT):
	$(MAKE_LIBFT)

clean:
	$(MAKE_LIBFT) $@
	$(MAKE_PROJECT)

fclean: clean
	$(MAKE_LIBFT) $@
	$(MAKE_PROJECT)

re: fclean all