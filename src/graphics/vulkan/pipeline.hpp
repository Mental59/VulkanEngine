#pragma once
#include <vector>
#include <vulkan/vulkan.h>

std::vector<char> readShaderFile(const char* filename);
VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);
