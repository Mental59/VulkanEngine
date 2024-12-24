#pragma once
#include <vector>
#include "vulkan/vulkan.h"

class GLFWwindow;

class HelloTriangleApplication
{
public:
	HelloTriangleApplication() = default;
	~HelloTriangleApplication();

	void run();

private:
	GLFWwindow* mWindow = nullptr;
	VkInstance mVulkanInstance = VK_NULL_HANDLE;

#ifdef _DEBUG
	VkDebugUtilsMessengerEXT mDebugMessenger = VK_NULL_HANDLE;
#endif

#ifdef _DEBUG
	PFN_vkCreateDebugUtilsMessengerEXT createDebugUtilsMessage = VK_NULL_HANDLE;
	PFN_vkDestroyDebugUtilsMessengerEXT destroyDebugUtilsMessage = VK_NULL_HANDLE;
#endif

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	void initWindow();
	void initVulkan();
	void createVulkanInstance();
	void setupDebugMessenger();
	VkDebugUtilsMessengerCreateInfoEXT getDebugMessengerCreateInfo();
	void initializeExtensionFunctions();

	void checkMandatoryExtensionsForSupport(const std::vector<const char*>& mandatoryExtensions);
	void checkValidationLayerSupport();
	bool isExtensionSupported(const char* extensionName, const std::vector<VkExtensionProperties>& supportedExtensions);
	std::vector<const char*> getMandatoryExtensions();

	void startMainLoop();

	void cleanup();
};
