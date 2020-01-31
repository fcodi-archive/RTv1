ifeq ($(DETECTED_OS),Darwin)
VULKANSDK_ARCHIVE = vulkansdk-macos.tar.gz.aa \
					vulkansdk-macos.tar.gz.ad \
					vulkansdk-macos.tar.gz.ag \
					vulkansdk-macos.tar.gz.ac \
					vulkansdk-macos.tar.gz.ah \
					vulkansdk-macos.tar.gz.af \
					vulkansdk-macos.tar.gz.ae \
					vulkansdk-macos.tar.gz.ab \
endif

ifeq ($(DETECTED_OS),Linux)
VULKANSDK_ARCHIVE = vulkansdk-linux.tar.gz.aa \
					vulkansdk-linux.tar.gz.ac \
					vulkansdk-linux.tar.gz.ab
endif

ifeq ($(DETECTED_OS),Darwin)
MOLTENVK_FRAMEWORK = $(MOLTENVK_DIR)/macOS/framework/MoltenVK.framework
endif
ifneq (,$(wildcard $(dir MOLTENVK_FRAMEWORK)/.))
CFLAGS_FRAMEWORKS += -F $(shell pwd)/$(MOLTENVK_FRAMEWORK) \
	-framework MoltenVK rpath $(shell pwd)/$(MOLTENVK_FRAMEWORK)
MOLTENVK_DIR = vulkansdk/MoltenVK
MOLTENVK_INCLUDE_DIR = $(MOLTENVK_DIR)/include
MOLTENVK_INCLUDE_DIR_LIST = $(MOLTENVK_INCLUDE_DIR) \
    						$(MOLTENVK_INCLUDE_DIR)/MoltenVK \
    						$(MOLTENVK_INCLUDE_DIR)/vulkan \
   							$(MOLTENVK_INCLUDE_DIR)/vulkan-portability
MOLTENVK_LIB_STATIC_DIR = $(MOLTENVK_DIR)/macOS/static
MOLTENVK_LIB_STATIC = libMoltenVK.a
MOLTENVK_LIB_DYNAMIC_DIR = $(MOLTENVK_DIR)/macOS/dynamic
MOLTENVK_LIB_DYNAMIC = libMoltenVK.dylib
MOLTENVK_ICD_D_DIR = $(MOLTENVK_LIB_DYNAMIC_DIR)
else
VULKAN_ICD_D_DIR = $(VULKAN_ETC)/vulkan/icd.d
endif

ifeq ($(DETECTED_OS),Darwin)
VULKAN_DIR = vulkansdk/macOS
endif

ifeq ($(DETECTED_OS),Linux)
VULKAN_DIR = vulkansdk/x86_64
endif

VULKAN_BIN_DIR = $(VULKAN_DIR)/bin
VULKAN_INCLUDE_DIR = $(VULKAN_DIR)/include
VULKAN_INCLUDE_DIR_LIST = $(VULKAN_DIR)/include \
						$(VULKAN_INCLUDE_DIR)/glslang \
						$(VULKAN_INCLUDE_DIR)/shaderc \
                      	$(VULKAN_INCLUDE_DIR)/SPIRV \
                      	$(VULKAN_INCLUDE_DIR)/spirv-tools \
                      	$(VULKAN_INCLUDE_DIR)/vulkan

ifeq ($(DETECTED_OS),Linux)
VULKAN_INCLUDE_DIR_LIST += $(VULKAN_INCLUDE_DIR)/spirv_cross
endif

VULKAN_LIB_DIR = $(VULKAN_DIR)/lib
VULKAN_LIB_STATIC_LIST = libglslang.a \
                  libHLSL.a \
                  libOGLCompiler.a \
                  libOSDependent.a \
                  libshaderc.a \
                  libshaderc_combined.a \
                  libSPIRV.a \
                  libspirv-cross.a \
                  libSPIRV-Tools.a \
                  libSPIRV-Tools-link.a \
                  libSPIRV-Tools-opt.a \
                  libSPIRV-Tools-reduce.a \
                  libSPVRemapper.a
VULKAN_LIB_DYNAMIC_LIST = libMoltenVK.dylib \
                          libshaderc_shared.1.dylib \
                          libshaderc_shared.dylib \
                          libSPIRV-Tools-shared.dylib \
                          libVkLayer_khronos_validation.dylib \
                          libvulkan.1.1.130.dylib \
                          libvulkan.1.dylib \
                          libvulkan.dylib
VULKAN_FRAMEWORK = $(VULKAN_DIR)/Frameworks/vulkan.framework
VULKAN_ETC = $(VULKAN_DIR)/etc
VULKAN_EXPLICIT_LAYER_D_DIR = $(VULKAN_ETC)/vulkan/explicit_layer.d

ifeq ($(DETECTED_OS),Linux)
CFLAGS_FRAMEWORKS += -F $(shell pwd)/$(VULKAN_FRAMEWORK) \
	-framework VulkanSDK rpath $(shell pwd)/$(VULKAN_FRAMEWORK)
endif
endif