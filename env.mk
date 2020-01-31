ifeq ($(ACCEPTED_OS),$(DETECTED_OS))

SH := $(shell finger $(shell whoami) | grep -o Shell:.*$ | grep -o "\ .*")
SHNAME := $(notdir $(SH))
SHRC := ~/.$(SHNAME)rc
SHRC_ORIGIN = $(SHRC).origin
SHRC_MOD := $(shell stat -f%p $(SHRC))

ifeq ($(DETECTED_OS),Darwin)
ifneq ($(wildcard $(MOLTENVK_FRAMEWORK).),)

ENV_MOLTEN_VK = MOLTEN_VK=$(shell pwd)/$(MOLTENVK_DIR)
ENV_VK_ICD_FILENAMES = \
	VK_ICD_FILENAMES=$(shell pwd)/$(MOLTENVK_LIB_DYNAMIC_DIR)/MoltenVK_icd.json
ENV_FRAMEWORK = $(shell pwd)/$(MOLTENVK_FRAMEWORK)
ENV_LIB = \
	$(shell pwd)/$(MOLTENVK_LIB_STATIC_DIR):$(shell pwd)/$(MOLTENVK_LIB_DYNAMIC_DIR)
ENV_INCLUDE = \
	$(addprefix $(shell pwd),$(MOLTENVK_INCLUDE_DIR_LIST))
else

ENV_VK_ICD_FILENAMES = \
    VK_ICD_FILENAMES=$(shell pwd)/$(VULKAN_ICD_D_DIR)/MoltenVK_icd.json

endif
endif

ENV_VULKAN_SDK = VULKAN_SDK=$(shell pwd)/$(VULKAN_DIR)
ENV_DYLD_LIBRARY_PATH = \
	DYLD_LIBRARY_PATH=$$VULKAN_SDK/lib:$DYLD_LIBRARY_PATH
ENV_VK_LAYER_PATH = \
	VK_LAYER_PATH=$(shell pwd)/$(VULKAN_EXPLICIT_LAYER_D_DIR)/explicit_layer.d

ifeq ($(DETECTED_OS),Linux)
ENV_LD_LIBRARY_PATH = LD_LIBRARY_PATH=$$VULKAN_SDK/lib:$LD_LIBRARY_PATH
endif

endif