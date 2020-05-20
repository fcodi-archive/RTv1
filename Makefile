# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/19 09:37:05 by fcodi             #+#    #+#              #
#    Updated: 2020/05/20 10:14:31 by fcodi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#	Pre-build
# **************************************************************************** #

-include settings.mk

ifneq ($(notdir $(CURDIR)),$(OBJECT_DIRECTORY))

.SUFFIXES:

include $(MK)/make_target.mk

$(eval $(call _MAKE_TARGET,MAKE_TARGET,\
	$(OBJECT_DIRECTORY),$(PREFIX)/Makefile,$(PREFIX)))

.PHONY: all $(NAME) debug

debug: all ; @

all: $(NAME)

$(NAME)::
	+@$(MAKE) --no-print-directory -C $(LIBFT_PATH) \
	$(filter all debug,$(MAKECMDGOALS))
	+@$(MAKE) --no-print-directory -C . -f $(LIBFT_MK_PATH)/sdl2.mk \
	PREFIX="$(PREFIX)"
$(NAME)::
	-@mkdir -p $(OBJECT_PATH)
	+@$(MAKE_TARGET)

clean::
	$(RM)r var $(OBJECT_PATH)
	+@$(MAKE) --no-print-directory -C . -f $(LIBFT_MK_PATH)/sdl2.mk \
	PREFIX="$(PREFIX)" $@
ifeq ($(findstring fclean re,$(MAKECMDGOALS)),)
clean::
	+@$(MAKE) --no-print-directory -C $(LIBFT_PATH) $@
endif

fclean::
ifneq ($(OS),Darwin)
fclean::
	$(RM) $(NAME).sh
endif
fclean:: clean
	$(RM) $(NAME)
	+@$(MAKE) --no-print-directory -C $(LIBFT_PATH) $@
	+@$(MAKE) --no-print-directory -C . -f $(LIBFT_MK_PATH)/sdl2.mk \
	PREFIX="$(PREFIX)" $@

re: fclean all

else

# **************************************************************************** #
#	Build
# **************************************************************************** #

include ../settings.mk
override CFLAGS += $(filter -I%, \
	$(shell $(MAKE) --no-print-directory -C $(LIBFT_PATH) _cflags) \
	$(shell $(PREFIX)/bin/sdl2-config --cflags))
override LDFLAGS += $(filter -L% -l%, \
	$(shell $(MAKE) --no-print-directory -C $(LIBFT_PATH) _ldflags) \
	$(shell $(PREFIX)/bin/sdl2-config --libs --static-libs))
INCLUDE_SEARCH += \
	$(shell $(MAKE) --no-print-directory -C $(LIBFT_PATH) _ipath) \
	$(foreach _PATH,$(CFLAGS),$(patsubst -I%,%,$(_PATH)))
include $(MK)/prefix.mk

all: $(NAME)

$(OBJECT_FILES): $(VARIABLE_FILES)

$(NAME): $(OBJECT_FILES) $(INCLUDE_FILES)
	$(CC) $(filter %.o,$^) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@

endif