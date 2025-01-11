#pragma once
#include <vector>
#include "vulkan/vulkan.h"
#include "debugMessenger.hpp"

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
	VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;
	VkDevice mDevice = VK_NULL_HANDLE;
	VkQueue mGraphicsQueue = VK_NULL_HANDLE;
	VkQueue mPresentQueue = VK_NULL_HANDLE;
	VkSurfaceKHR mSurface = VK_NULL_HANDLE;
	VkSwapchainKHR mSwapChain = VK_NULL_HANDLE;
	VkFormat mSwapChainImageFormat;
	VkExtent2D mSwapChainExtent;

	std::vector<VkImage> mSwapChainImages;
	std::vector<VkImageView> mSwapChainImageViews;

#ifdef _DEBUG
	DebugMessenger mDebugMessenger;
#endif

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	void initWindow();
	void initVulkan();
	void createVulkanInstance();
	void createSwapChain();
	void createImageViews();
	void initDebugMessenger();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	bool isDeviceSuitable(const VkPhysicalDevice device) const;
	bool checkDeviceExtensionSupport(const VkPhysicalDevice device) const;

	void checkMandatoryExtensionsForSupport(const std::vector<const char*>& mandatoryExtensions);
	void checkValidationLayerSupport();
	bool isExtensionSupported(const char* extensionName, const std::vector<VkExtensionProperties>& supportedExtensions);
	std::vector<const char*> getMandatoryExtensions();

	void startMainLoop();

	void cleanup();
};
