#include "queue.hpp"
#include <vector>
#include <vulkan/vulkan_core.h>

bool QueueFamilyIndices::isComplete() const
{
	return graphicsFamily.has_value();
}

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	if (queueFamilyCount == 0)
	{
		return indices;
	}

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	for (uint32_t i = 0; i < queueFamilyCount; i++)
	{
		if (indices.isComplete())
		{
			break;
		}

		if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}
	}

	return indices;
}
