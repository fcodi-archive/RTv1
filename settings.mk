# **************************************************************************** #
#	Settings
# **************************************************************************** #

FILTER_RULES = all debug

PREFIX = $(CURDIR)

OBJECT_DIRECTORY = .obj

OBJECT_PATH ?= $(PREFIX)/$(OBJECT_DIRECTORY)

INCLUDE_DIRECTORY ?= include

INCLUDE_PATH ?= $(PREFIX)/$(INCLUDE_DIRECTORY)

LIBFT_MK_PATH ?= $(LIBFT_PATH)/mk

-include libft/mk/libft.mk
-include $(LIBFT_MK_PATH)/libft.mk

MK = $(LIBFT_MK_PATH)

# **************************************************************************** #
#	RTv1 sources
# **************************************************************************** #

NAME := $(PREFIX)/RTv1

SOURCE_FILES = camera.c \
	sdl.c \
	hit_objects.c \
	parse_type.c \
	raytracer.c \
	parse_field.c \
	scene_manager_checklist.c \
	scene_manager.c \
	parse_scene.c \
	init_scene.c \
	parse_point3d.c \
	light.c \
	scene.c \
	color.c \
	ft_vector.c \
	objects_normals.c \
	parse_color.c \
	object.c \
	parse_double.c \
	main.c \
	parse_option.c \
	point3d.c \
	set_current_parse_element.c

INCLUDE_FILES = structs.h \
	rtv1.h \
	ft_sdl.h \
	color.h \
	ft_vector.h \
	point3d.h