#include <glfw/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <cstring>
#include <vector>
#include <format>
#include "helloTriangleApp.hpp"
#include "graphics/vulkan/queue.hpp"

static constexpr int WINDOW_WIDTH = 1280;
static constexpr int WINDOW_HEIGHT = 720;

const std::vector<const char*> VALIDATION_LAYERS = {"VK_LAYER_KHRONOS_validation"};

HelloTriangleApplication::~HelloTriangleApplication()
{
	cleanup();
}

void HelloTriangleApplication::run()
{
	initWindow();
	initVulkan();
	startMainLoop();
}

void HelloTriangleApplication::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return;
	}
}

void HelloTriangleApplication::initWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	mWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan", nullptr, nullptr);

	glfwSetKeyCallback(mWindow, keyCallback);
}

void HelloTriangleApplication::initVulkan()
{
	createVulkanInstance();
	initDebugMessenger();
	pickPhysicalDevice();
	createLogicalDevice();
}

void HelloTriangleApplication::createVulkanInstance()
{
	checkValidationLayerSupport();

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceCreateInfo{};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.pApplicationInfo = &appInfo;

	std::vector<const char*> mandatoryExtensions = getMandatoryExtensions();

#ifdef _DEBUG
	std::cout << "Mandatory extensions: ";
	for (uint32_t i = 0; i < mandatoryExtensions.size() - 1; i++)
	{
		std::cout << mandatoryExtensions[i] << ", ";
	}
	std::cout << mandatoryExtensions[mandatoryExtensions.size() - 1] << std::endl;
#endif

	checkMandatoryExtensionsForSupport(mandatoryExtensions);

	instanceCreateInfo.enabledExtensionCount = mandatoryExtensions.size();
	instanceCreateInfo.ppEnabledExtensionNames = mandatoryExtensions.data();

#ifdef _DEBUG
	instanceCreateInfo.enabledLayerCount = VALIDATION_LAYERS.size();
	instanceCreateInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();

	VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo = mDebugMessenger.getDebugMessengerCreateInfo();
	instanceCreateInfo.pNext = &debugMessengerCreateInfo;
#else
	instanceCreateInfo.enabledLayerCount = 0;
#endif

	if (vkCreateInstance(&instanceCreateInfo, nullptr, &mVulkanInstance) != VK_SUCCESS)
	{
		throw std::runtime_error("ERROR: failed to create vulkan instance");
	}
}

void HelloTriangleApplication::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;

	vkEnumeratePhysicalDevices(mVulkanInstance, &deviceCount, nullptr);
	if (deviceCount == 0)
	{
		throw std::runtime_error("ERROR: failed to find GPUs with Vulkan support");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(mVulkanInstance, &deviceCount, devices.data());

	for (const VkPhysicalDevice device : devices)
	{
		if (isDeviceSuitable(device))
		{
			mPhysicalDevice = device;
			break;
		}
	}

	if (mPhysicalDevice == VK_NULL_HANDLE)
	{
		throw std::runtime_error("ERROR: failed to find a suitable GPU");
	}
}

void HelloTriangleApplication::initDebugMessenger()
{
#ifdef _DEBUG
	mDebugMessenger.init(mVulkanInstance);
#endif
}

void HelloTriangleApplication::createLogicalDevice()
{
	QueueFamilyIndices indices = findQueueFamilies(mPhysicalDevice);

	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0;

#ifdef _DEBUG
	createInfo.enabledLayerCount = static_cast<uint32_t>(VALIDATION_LAYERS.size());
	createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
#else
	createInfo.enabledLayerCount = 0;
#endif

	if (vkCreateDevice(mPhysicalDevice, &createInfo, nullptr, &mDevice) != VK_SUCCESS)
	{
		throw std::runtime_error("ERROR: failed to create logical device!");
	}

	vkGetDeviceQueue(mDevice, indices.graphicsFamily.value(), 0, &mGraphicsQueue);
}

bool HelloTriangleApplication::isDeviceSuitable(const VkPhysicalDevice device) const
{
	QueueFamilyIndices indices = findQueueFamilies(device);

	return indices.isComplete();
}

void HelloTriangleApplication::checkMandatoryExtensionsForSupport(const std::vector<const char*>& mandatoryExtensions)
{
	uint32_t supportedExtensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionCount, nullptr);
	std::vector<VkExtensionProperties> supportedExtensions(supportedExtensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &supportedExtensionCount, supportedExtensions.data());

#ifdef _DEBUG
	std::cout << "Supported extensions: ";
	for (uint32_t i = 0; i < supportedExtensionCount - 1; i++)
	{
		std::cout << supportedExtensions[i].extensionName << ", ";
	}
	std::cout << supportedExtensions[supportedExtensionCount - 1].extensionName << std::endl;
#endif	// DEBUG

	for (const char* mandatoryExtension : mandatoryExtensions)
	{
		if (!isExtensionSupported(mandatoryExtension, supportedExtensions))
		{
			throw std::runtime_error(
				std::format("ERROR: mandatory extension {} is not supported on this platform", mandatoryExtension));
		}
	}
}

void HelloTriangleApplication::checkValidationLayerSupport()
{
#ifdef _DEBUG
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : VALIDATION_LAYERS)
	{
		bool layerFound = false;

		for (const VkLayerProperties& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
		{
			throw std::runtime_error("ERROR: validation layers requested, but not available!");
		}
	}
#endif
}

bool HelloTriangleApplication::isExtensionSupported(
	const char* extensionName, const std::vector<VkExtensionProperties>& supportedExtensions)
{
	for (const VkExtensionProperties& supportedExtension : supportedExtensions)
	{
		if (strcmp(extensionName, supportedExtension.extensionName) == 0)
		{
			return true;
		}
	}
	return false;
}

std::vector<const char*> HelloTriangleApplication::getMandatoryExtensions()
{
	uint32_t mandatoryExtensionCount = 0;
	const char** mandatoryExtensionNames = glfwGetRequiredInstanceExtensions(&mandatoryExtensionCount);
	std::vector<const char*> mandatoryExtensionVector(
		mandatoryExtensionNames, mandatoryExtensionNames + mandatoryExtensionCount);

#ifdef _DEBUG
	mandatoryExtensionVector.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif	// _DEBUG

	return mandatoryExtensionVector;
}

void HelloTriangleApplication::startMainLoop()
{
	while (!glfwWindowShouldClose(mWindow))
	{
		glfwPollEvents();
	}
}

void HelloTriangleApplication::cleanup()
{
#ifdef _DEBUG
	mDebugMessenger.cleanup();
#endif

	vkDestroyDevice(mDevice, nullptr);
	vkDestroyInstance(mVulkanInstance, nullptr);
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}
