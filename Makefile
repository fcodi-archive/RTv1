.PHONY : all re clean fclean check test backup

.ONESHELL :

include oscheck.mk vulkan.mk env.mk

LIBFT = libft.a

NAME = RTv1

UNAME := $(shell uname)

SH := $(shell finger $(shell whoami) | grep -o Shell:.*$ | grep -o "\ .*")

VKVIA = $(shell find . -name "vkvia")

SHNAME := $(notdir $(SH))

SHRC_ORIGIN = $(SHRC).origin

SHRC := ~/.$(SHNAME)rc

SHRC_MOD := $(shell stat -f%p $(SHRC))

ENV_VULKAN_BIN = PATH=$$VULKAN_SDK/bin:$$PATH

ENV_DYLD_LIBRARY_PATH = \
	DYLD_LIBRARY_PATH=$$VULKAN_SDK/lib:$DYLD_LIBRARY_PATH

ENV_VK_ICD_FILENAMES = \
	VK_ICD_FILENAMES=$$VULKAN_SDK/etc/vulkan/icd.d/MoltenVK_icd.json

ENV_VK_LAYER_PATH = VK_LAYER_PATH=$$VULKAN_SDK/etc/vulkan/explicit_layer.d

ENV_MOLTEN_VK = MOLTEN_VK=$(MOLTEN_VK_DIR)

ENV_MOLTEN_VK_LIB = \
	PATH=$$MOLTEN_VK/macOS/dynamic:$$MOLTEN_VK/macOS/static:$$PATH

ENV_MOLTEN_VK_FRAMEWORK = PATH=$$MOLTEN_VK/macOS/framework:$$PATH

ENV_MOLTEN_VK_INCLUDE = PATH=$$MOLTEN_VK/include:$$PATH

VULKANSDK := $(shell pwd)/vulkansdk

SET_ENV = $(SHRC).mk

ifeq ($(UNAME),Darwin)
	ENV_VULKAN_SDK = VULKAN_SDK=$(shell pwd)/vulkansdk/macOS
	VULKANSDK_ARCHIVE = vulkansdk-macos.tar.gz.aa \
						vulkansdk-macos.tar.gz.ab \
						vulkansdk-macos.tar.gz.ac \
						vulkansdk-macos.tar.gz.ad
endif

ifeq ($(UNAME),Linux)
	ENV_VULKAN_SDK = $(shell pwd)/x86_64
	ENV_LD_LIBRARY_PATH = LD_LIBRARY_PATH=$VULKAN_SDK/lib:$LD_LIBRARY_PATH
	VULKANSDK_ARCHIVE = vulkansdk-linux.tar.gz.aa \
						vulkansdk-linux.tar.gz.ab
endif

all:
	@echo $(PATH):$(subst $(space),:,$(ENV_INCLUDE)):$(PATH)
#all :: $(VULKANSDK) $(LIBFT)
#all :: $(NAME)

$(NAME) : $(LIBFT)

backup :
	@echo "Unsetting environment"
	@chmod 777 $(SHRC)
	@chmod 777 $(SHRC_ORIGIN)
	@cat $(SHRC_ORIGIN) > $(SHRC)
	@chmod $(SHRC_MOD) $(SHRC)
	@chmod $(SHRC_MOD) $(SHRC_ORIGIN)
	@$(RM) $(SET_ENV)

$(VKVIA) :
	$(error Utily vkvia not found. Check availability of vulkansdk)

test : check
check : $(VULKANSDK) $(VKVIA)

uninstall :
	rm -rf vulkansdk

$(VULKANSDK) : $(SET_ENV)
	@echo "Unpacking vulkansdk"
	@cat $(VULKANSDK_ARCHIVE) | tar xzvf -
$(VULKANSDK) : $(VKVIA)

$(SET_ENV) : $(SHRC_ORIGIN)
	@echo "Setting environment"
	@touch $(SET_ENV)
	@chmod 777 $(SHRC)
	@export $(ENV_VULKAN_SDK) >> $(SHRC)
	@export $(ENV_VULKAN_BIN) >> $(SHRC)
	@export $(ENV_VK_ICD_FILENAMES) >> $(SHRC)
	@export $(ENV_VK_LAYER_PATH) >> $(SHRC)
	ifeq ($(UNAME),Darwin)
		@export $(ENV_VK_INSTANCE_LAYERS) >> $(SHRC)
		@export $(ENV_DYLD_LIBRARY_PATH) >> $(SHRC)
		@export $(ENV_MOLTEN_VK) >> $(SHRC)
		@export $(ENV_MOLTEN_VK_LIB) >> $(SHRC)
		@export $(ENV_MOLTEN_VK_FRAMEWORK) >> $(SHRC)
		@export $(ENV_MOLTEN_VK_INCLUDE) >> $(SHRC)
	endif
	ifeq ($(UNAME),Linux)
		@export $(ENV_LD_LIBRARY_PATH) >> $(SHRC)
	endif
	@chmod $(SHRC_MOD) $(SHRC)

$(SHRC_ORIGIN) :
	@echo "Creating backup of environment"
	@chmod 777 $(SHRC)
	@cp $(SHRC) $(SHRC_ORIGIN)
	@chmod $(SHRC_MOD) $(SHRC)
	@chmod $(SHRC_MOD) $(SHRC_ORIGIN)

clean :

fclean : clean

re : fclean

#vpath %.a libft:vulkansdk/MoltenVK/macOS/static:vulkansdk/macOS/lib
#vpath %.h libft:$(MOLTENVK_INCLUDE)/MoltenVK:$(MOLTENVK_INCLUDE)/vulkan:$(MOLTENVK_INCLUDE)/vulkan-portability