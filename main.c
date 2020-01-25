#include "RTv1.h"

/**
 *
 * @param application_info
 */

void	init_application_info(VkApplicationInfo *application_info)
{
	application_info->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	application_info->pNext = NULL;
	application_info->apiVersion = VK_API_VERSION_1_0;
	application_info->pApplicationName = "Hello, Vulkan!";
	application_info->applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	application_info->pEngineName = "DzEngine";
	application_info->engineVersion = VK_MAKE_VERSION(1, 0, 0);;
}

/**
 *
 * @param instance_info
 */

void	init_instance_info(VkInstanceCreateInfo *instance_info)
{
	VkApplicationInfo		application_info;

	init_application_info(&application_info);
	instance_info->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instance_info->pNext = NULL;
	instance_info->flags = 0;
	instance_info->pApplicationInfo = &application_info;
	instance_info->enabledLayerCount = 0;
	instance_info->enabledExtensionCount = 0;
	instance_info->ppEnabledExtensionNames = NULL;
	instance_info->ppEnabledLayerNames = NULL;
}

/**
 *
 * @param instance
 *
 * Only if VkResult result == VK_SUCCESS CreateInstance complete well
 *
 */

void	init_instance(VkInstance *instance)
{
	VkInstanceCreateInfo	instance_info;
	VkResult				result;

	init_instance_info(&instance_info);
	if ((result = vkCreateInstance(&instance_info, NULL, instance))
		== VK_ERROR_INCOMPATIBLE_DRIVER)
	{
		ft_putstr("Cannot find a compatible Vulkan ICD\n");
		exit(EXIT_FAILURE);
	}
	else if (result)
	{
		ft_putstr("Unknown error\n");
		exit(EXIT_FAILURE);
	}
}

int 	main(int argc, char **argv)
{
	VkInstance				instance;

	init_instance(&instance);
	vkDestroyInstance(instance, NULL);
	return (EXIT_SUCCESS);
}