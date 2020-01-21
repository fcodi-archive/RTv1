WORKING_DIRECTORY := $(shell pwd)

MOLTEN_VK = $(shell pwd)/MoltenVK

VULKAN_SDK = $(shell pwd)/VulkanSDK

BREW_OPT_DIR = $(HOME)/.brew/opt

BREW_BIN_DIR = $(HOME)/.brew/bin

WGET = $(BREW_BIN_DIR)/wget

BREW = $(BREW_BIN_DIR)/brew

JAVA = $(BREW_OPT_DIR)/openjdk/bin/java

all : BREW

VULKAN_SDK : MOLTEN_VK WGET
	@if [ ! -d $(VULKAN_SDK) ]; \
	then \
		wget -O - https://sdk.lunarg.com/sdk/download/1.1.130.0/mac/vulkansdk-macos-1.1.130.0.tar.gz?Human=True | tar -xvgfzC $(VULKAN_SDK) - ; \
	fi

MOLTEN_VK :
	@if [ ! -d $(MOLTEN_VK) ]; \
	then \
	git submodule init ; \
	git submodule add https://github.com/KhronosGroup/MoltenVK.git ; \
	git submodule update --recursive ; \
	fi

WGET : BREW JAVA
	@if [ ! -s $(WGET) ]; \
	then \
		brew install wget ; \
	fi

JAVA : BREW
	@if [ ! -d $(JAVA) ]; \
	then \
		brew install openjdk ; \
		echo 'export PATH="/Users/fcodi/.brew/opt/openjdk/bin:$$PATH"' >> ~/.zshrc ; \
	fi

BREW :
	@if [ ! -s $(BREW) ]; \
	then \
		curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh | sh -c ; \
	fi