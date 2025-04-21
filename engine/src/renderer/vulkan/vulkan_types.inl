#pragma once

#include "../../core/asserts.h"
#include "../../defines.h"
#include <vulkan/vulkan.h>

#define VK_CHECK(expr)           \
  {                              \
    KASSERT(expr == VK_SUCCESS); \
  }

typedef struct vulkan_context
{
  VkInstance instance;
  VkAllocationCallbacks *allocator;
} vulkan_context;