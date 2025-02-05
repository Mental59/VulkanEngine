#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <array>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Color;

	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions();
};
