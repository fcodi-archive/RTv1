.PHONY : all re clean fclean check test backup

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

BREW = ~/.brew/bin/brew

BREW_URL = \
	https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh

PV = $(shell brew list pv | grep /bin/pv )

ifeq ($(UNAME),Darwin)
	ENV_VULKAN_SDK = VULKAN_SDK=$(shell pwd)/vulkansdk/macOS
	VULKANSDK_INSTALL = @pv $(VULKANSDK_ARCHIVE) | tar xzvf - > /dev/null 2>&1
	VULKANSDK_ARCHIVE = vulkansdk-macos.tar.gz.aa \
						vulkansdk-macos.tar.gz.ab \
						vulkansdk-macos.tar.gz.ac \
						vulkansdk-macos.tar.gz.ad
endif

ifeq ($(UNAME),Linux)
	VULKANSDK_INSTALL = @cat $(VULKANSDK_ARCHIVE) | tar xzvf -
	ENV_VULKAN_SDK = $(shell pwd)/x86_64
	ENV_LD_LIBRARY_PATH = LD_LIBRARY_PATH=$VULKAN_SDK/lib:$LD_LIBRARY_PATH
	VULKANSDK_ARCHIVE = vulkansdk-linux.tar.gz.aa \
						vulkansdk-linux.tar.gz.ab
endif

NAME = RTv1

all : $(VULKANSDK)
#all :: $(LIBFT)
#all :: $(NAME)

$(PV) : $(BREW)
	@echo $(PV)
ifeq ($(UNAME),Darwin)
	@echo "Install pv (console progressbar)"
	@brew install pv
endif

$(BREW) :
ifeq ($(UNAME),Darwin)
	sh -c "$(curl -fsSL $(BREW_URL))"
endif

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

backup :
	@echo "Unsetting environment"
	@chmod 777 $(SHRC)
	@chmod 777 $(SHRC_ORIGIN)
	@cat $(SHRC_ORIGIN) > $(SHRC)
	@chmod $(SHRC_MOD) $(SHRC)
	@chmod $(SHRC_MOD) $(SHRC_ORIGIN)
	@$(RM) $(SET_ENV)

$(VULKANSDK) : $(SET_ENV) $(PV)
	@echo "Unpacking vulkansdk"
	$(VULKANSDK_INSTALL)
$(VULKANSDK) : $(VKVIA)

$(VKVIA) :
	$(error Utily vkvia not found. Check availability of vulkansdk)

test : check
check : $(VULKANSDK) $(VKVIA)

uninstall :
	rm -rf vulkansdk
	#brew uninstall pv