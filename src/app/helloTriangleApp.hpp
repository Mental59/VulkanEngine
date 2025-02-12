#pragma once
#include <vector>
#include <array>
#include "vulkan/vulkan.h"
#include "debugMessenger.hpp"

class GLFWwindow;

constexpr size_t MAX_FRAMES_IN_FLIGHT = 2;

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
	VkFormat mSwapChainImageFormat{};
	VkExtent2D mSwapChainExtent{};
	VkRenderPass mRenderPass = VK_NULL_HANDLE;
	VkDescriptorSetLayout mDescriptorSetLayout = VK_NULL_HANDLE;
	VkPipelineLayout mPipelineLayout = VK_NULL_HANDLE;
	VkPipeline mGraphicsPipeline = VK_NULL_HANDLE;
	VkCommandPool mCommandPool = VK_NULL_HANDLE;
	VkBuffer mVertexBuffer = VK_NULL_HANDLE;
	VkBuffer mIndexBuffer = VK_NULL_HANDLE;
	VkDeviceMemory mVertexBufferMemory = VK_NULL_HANDLE;
	VkDeviceMemory mIndexBufferMemory = VK_NULL_HANDLE;
	VkDescriptorPool mDescriptorPool = VK_NULL_HANDLE;
	std::array<VkCommandBuffer, MAX_FRAMES_IN_FLIGHT> mCommandBuffers;
	std::array<VkSemaphore, MAX_FRAMES_IN_FLIGHT> mImageAvailableSemaphores;
	std::array<VkSemaphore, MAX_FRAMES_IN_FLIGHT> mRenderFinishedSemaphores;
	std::array<VkFence, MAX_FRAMES_IN_FLIGHT> mInFlightFences;
	std::array<VkBuffer, MAX_FRAMES_IN_FLIGHT> mUniformBuffers;
	std::array<VkDeviceMemory, MAX_FRAMES_IN_FLIGHT> mUniformBuffersMemory;
	std::array<void*, MAX_FRAMES_IN_FLIGHT> mUniformBuffersMapped;
	std::array<VkDescriptorSet, MAX_FRAMES_IN_FLIGHT> mDescriptorSets;

	std::vector<VkImage> mSwapChainImages;
	std::vector<VkImageView> mSwapChainImageViews;
	std::vector<VkFramebuffer> mSwapChainFramebuffers;

	bool mFramebufferResized = false;

#ifdef _DEBUG
	DebugMessenger mDebugMessenger;
#endif

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	void initWindow();
	void initVulkan();
	void startMainLoop();
	void cleanup();
	void cleanupSwapchain();

	void createVulkanInstance();
	void initDebugMessenger();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createDescriptorSetLayout();
	void createGraphicsPipeline();
	void createFramebuffers();
	void createCommandPool();
	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffers();
	void createDescriptorPool();
	void createDescriptorSets();
	void createCommandBuffer();
	void createSyncObjects();

	void recreateSwapchain();

	void update(uint32_t currentFrame, double deltaTime, double lastFrameTime);
	void drawFrame(uint32_t currentFrame);

	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, uint32_t currentFrame);

	bool isDeviceSuitable(const VkPhysicalDevice device) const;
	bool checkDeviceExtensionSupport(const VkPhysicalDevice device) const;
	void checkMandatoryExtensionsForSupport(const std::vector<const char*>& mandatoryExtensions);
	void checkValidationLayerSupport();
	bool isExtensionSupported(const char* extensionName, const std::vector<VkExtensionProperties>& supportedExtensions);
	std::vector<const char*> getMandatoryExtensions();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer,
		VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
};
