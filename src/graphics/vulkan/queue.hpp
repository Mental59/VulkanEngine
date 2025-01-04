#pragma once
#include <cstdint>
#include <vulkan/vulkan_core.h>
#include <optional>

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;

	bool isComplete() const;
};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
