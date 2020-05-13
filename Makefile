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
	parse_option.c

INCLUDE_FILES = color.h \
	ft_vector.h \
	RTv1.h \
	ft_SDL.h \
	point3d.h \
	render.h

include libft/mk/project.mk

# **************************************************************************** #
#	SDL2
# **************************************************************************** #

SDL2_TAR_GZ = $(PROJECT_PATH)/SDL2-2.0.12.tar.gz

SDL2_DIRECTORY = SDL2-2.0.12

SDL2_PATH = $(PROJECT_PATH)/$(SDL2_DIRECTORY)

SDL2_BUILD_PATH = $(SDL2_PATH)/build

SDL2_BUILD_PATH_EXIST = $(SDL2_BUILD_PATH)/.exist

SDL2_CONFIGURE = $(SDL2_PATH)/configure

SDL2_BUILD_PATH = $(SDL2_PATH)/build

SDL2_BUILD_PATH_EXIST = $(SDL2_BUILD_PATH)/.exist

SDL2_BUILD_MAKEFILE = $(SDL2_BUILD_PATH)/Makefile

SDL2_INCLUDE = $(INCLUDE_PATH)/SDL2

LOG_DIRECTORY ?= log

LOG_PATH ?= $(PROJECT_PATH)/$(LOG_DIRECTORY)

LOG_PATH_EXIST = $(LOG_PATH)/.exist

SDL2_ERROR_LOG = $(LOG_PATH)/sdl2_build_error.log

BINNARY_DIRECTORY = bin

BINNARY_PATH = $(PROJECT_PATH)/bin

SDL2_CONFIG = $(BINNARY_PATH)/sdl2-config

LIBSDL2 = $(PROJECT_PATH)/lib/libSDL2.a

override LDFLAGS += $(subst $(COMMA),$(SPACE), \
	$(strip $(shell $(SDL2_CONFIG) --libs --static-libs)))
override CFLAGS += $(filter -I%,$(shell $(SDL2_CONFIG) --cflags))
override CPPFLAGS += $(filter-out -I%,$(shell $(SDL2_CONFIG) --cflags))

.PHONY: clean_sdl2 fclean_sdl2

all: $(LIBSDL2)

$(LIBSDL2): $(SDL2_BUILD_MAKEFILE)
	+@$(MAKE) --no-print-directory -C $(SDL2_BUILD_PATH) install \
	2> $(SDL2_ERROR_LOG)

clean_sdl2:
	$(RMDIR) $(SDL2_PATH)

clean: clean_sdl2

#	TODO Верните пжлст полное вычещение SDL2
#	fclean_sdl2: clean_sdl2
fclean_sdl2:
	$(RMDIR) $(shell find $(PROJECT_PATH) -iregex ".*sdl.*" | \
	grep -Ev ".*($(SDL2_DIRECTORY)|src|include).*") $(SDL2_INCLUDE)

fclean: fclean_sdl2

re: fclean_sdl2 $(LIBSDL2)

$(SDL2_BUILD_MAKEFILE): $(LOG_PATH_EXIST)
$(SDL2_BUILD_MAKEFILE): $(SDL2_CONFIGURE) $(SDL2_BUILD_PATH_EXIST)
	cd $(SDL2_BUILD_PATH); ../configure \
	--exec_prefix=$(PROJECT_PATH) \
	--prefix=$(PROJECT_PATH) \
	--datadir=$(PROJECT_PATH)
	+@$(MAKE) --no-print-directory -C $(SDL2_BUILD_PATH) \
	2> $(SDL2_ERROR_LOG)

$(SDL2_CONFIGURE):
	tar -xvzf $(SDL2_TAR_GZ)

# **************************************************************************** #
#	Rules
# **************************************************************************** #

all: $(NAME)

$(NAME):
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)

clean:
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)

fclean:
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)

re:
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)