#include <iostream>
#include "debugMessenger.hpp"

void DebugMessenger::cleanup()
{
	if (mVulkanInstance != VK_NULL_HANDLE && destroyDebugUtilsMessage != VK_NULL_HANDLE)
	{
		destroyDebugUtilsMessage(mVulkanInstance, mDebugMessenger, nullptr);
	}
}

void DebugMessenger::init(VkInstance vulkanInstance)
{
	mVulkanInstance = vulkanInstance;

	initializeExtensionFunctions();
	VkDebugUtilsMessengerCreateInfoEXT createInfo = getDebugMessengerCreateInfo();
	if (createDebugUtilsMessage(mVulkanInstance, &createInfo, nullptr, &mDebugMessenger) != VK_SUCCESS)
	{
		throw std::runtime_error("ERROR: failed to create debug messenger");
	}
}

VKAPI_ATTR VkBool32 VKAPI_CALL DebugMessenger::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	std::cerr << "Validation layer message: " << pCallbackData->pMessage << std::endl;
	return VK_FALSE;
}

VkDebugUtilsMessengerCreateInfoEXT DebugMessenger::getDebugMessengerCreateInfo()
{
	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
								 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
								 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
	return createInfo;
}

void DebugMessenger::initializeExtensionFunctions()
{
	createDebugUtilsMessage =
		(PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mVulkanInstance, "vkCreateDebugUtilsMessengerEXT");
	destroyDebugUtilsMessage =
		(PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mVulkanInstance, "vkDestroyDebugUtilsMessengerEXT");

	if (!createDebugUtilsMessage || !destroyDebugUtilsMessage)
	{
		throw std::runtime_error("ERROR: failed to initialize debug extension functions");
	}
}
