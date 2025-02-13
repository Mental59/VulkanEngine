#pragma once

#include <glm/ext/vector_float3.hpp>

namespace Direction
{
constexpr glm::vec3 FORWARD(0.0f, 0.0f, 1.0f);
constexpr glm::vec3 UP(0.0f, -1.0f, 0.0f);
constexpr glm::vec3 RIGHT(1.0f, 0.0f, 0.0f);
constexpr glm::vec3 CENTER(0.0f);
}  // namespace Direction
