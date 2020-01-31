#ifndef FT_VULKAN_H
# define FT_VULKAN_H

# ifdef __APPLE__
#  include "vulkansdk/MoltenVK/include/MoltenVK/mvk_vulkan.h"
# endif

# ifdef __linux__
#  include <vulkan.h> //TODO прописать полный путь до шапки Vulkan SDK Linux
# endif

#endif