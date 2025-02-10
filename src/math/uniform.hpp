#pragma once

#include <glm/ext/matrix_float4x4.hpp>

struct UniformBufferObject
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};
