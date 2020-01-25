WORKING_DIRECTORY := $(shell pwd)

VULKAN_SDK = $(shell pwd)/VulkanSDK

BREW_OPT_DIR = $(HOME)/.brew/opt

BREW_BIN_DIR = $(HOME)/.brew/bin

WGET = $(BREW_BIN_DIR)/wget

BREW = $(BREW_BIN_DIR)/brew

JAVA = $(BREW_OPT_DIR)/openjdk/bin/java

all : BREW

VULKAN_SDK :
	@if [ ! -d $(VULKAN_SDK) ]; \
	then \
		wget -O - https://sdk.lunarg.com/sdk/download/latest/mac/vulkan-sdk.tar.gz | tar -xzf - ; \
	fi

WGET : BREW JAVA
	@if [ ! -s $(WGET) ]; \
	then \
		brew install wget ; \
		echo 'export PATH="/Users/fcodi/.brew/opt/gettext/bin:$PATH"' >> ~/.zshrc ; \
		echo 'export PATH="/Users/fcodi/.brew/opt/openssl@1.1/bin:$PATH"' >> ~/.zshrc ; \
		echo 'export PATH="/Users/fcodi/.brew/opt/gettext/bin:$PATH"' >> ~/.zshrc ; \
		echo 'export LC_ALL=en_US.UTF-8' >> ~/.zshrc ; \
	fi

JAVA : BREW
	@if [ ! -d $(JAVA) ]; \
	then \
		brew install openjdk ; \
		echo 'PATH=/Users/fcodi/.brew/opt/openjdk/bin:$PATH' >> ~/.zshrc.test ; \
	fi

BREW :
	@if [ ! -s $(BREW) ]; \
	then \
		curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh > install_brew.sh ; \
		sh install_brew.sh ; \
	fi