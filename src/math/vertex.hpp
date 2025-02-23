#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <vulkan/vulkan.h>
#include <array>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Color = glm::vec3(1.0f);
	glm::vec2 TexCoord;

	bool operator==(const Vertex& other) const;

	static VkVertexInputBindingDescription getBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};

namespace std
{
template <>
struct hash<Vertex>
{
	size_t operator()(Vertex const& vertex) const
	{
		size_t hashedPos = hash<glm::vec3>()(vertex.Position);
		size_t hashedColor = hash<glm::vec3>()(vertex.Color);
		size_t hashedTexCoord = hash<glm::vec2>()(vertex.TexCoord);

		return ((hashedPos ^ (hashedColor << 1)) >> 1) ^ (hashedTexCoord << 1);
	}
};
}  // namespace std
