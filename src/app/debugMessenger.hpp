#pragma once
#include "vulkan/vulkan.h"

class DebugMessenger
{
public:
	DebugMessenger() = default;
	void cleanup();

	void init(VkInstance vulkanInstance);
	VkDebugUtilsMessengerCreateInfoEXT getDebugMessengerCreateInfo();

private:
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	void initializeExtensionFunctions();

	PFN_vkCreateDebugUtilsMessengerEXT createDebugUtilsMessage = VK_NULL_HANDLE;
	PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugUtilsMessage = VK_NULL_HANDLE;

	VkInstance mVulkanInstance = VK_NULL_HANDLE;
	VkDebugUtilsMessengerEXT mDebugMessenger = VK_NULL_HANDLE;
};
