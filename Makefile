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