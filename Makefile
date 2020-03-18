.PHONY: all re clean fclean libft

include libft/mk/libft.mk

include $(LIBFT_MK_PATH)/project.mk

include $(LIBFT_MK_PATH)/sdl.mk

RMDIR := $(RM)r

NAME = RTv1

LINK_PATH = $(LIBFT_PATH) $(BREW_LIB_PATH)

LINK_NAME = $(LIBFT_SUFFIX) $(LIBSDL_SUFFIX)

LIB_PATH_FLAG += $(addprefix -L,$(LINK_PATH))

LIB_NAME_FLAG += $(addprefix -l,$(LINK_NAME))

INCLUDE_PATH += $(SDL_INCLUDE_PATH)

VPATHS = $(SDL_INCLUDE_PATH)

MAKE_PROJECT += LIB_PATH_FLAG="$(LIB_PATH_FLAG)" \
	LIB_NAME_FLAG="$(LIB_NAME_FLAG)" \
	VPATHS="$(VPATHS)"

SRC = main.c

all: $(MAKE_SDL)
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)

clean:
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)

fclean:
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)

re: $(MAKE_SDL)
	$(MAKE_LIBFT)
	$(MAKE_PROJECT)