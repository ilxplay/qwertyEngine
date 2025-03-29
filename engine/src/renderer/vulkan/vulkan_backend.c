#pragma GCC diagnostic ignored "-Wreturn-type"
#include "vulkan_backend.h"
#include "vulkan_types.inl"
#include "../../core/logger.h"

static vulkan_context context;

b8 vulkan_renderer_backend_initialize(renderer_backend *renderer_backend, const char *application_name, struct platform_state *plat_state)
{

  context.allocator = 0;

  VkApplicationInfo app_info = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
  app_info.apiVersion = VK_API_VERSION_1_4;
  app_info.pApplicationName = application_name;
  app_info.pEngineName = "Qwerty Engine";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);

  VkInstanceCreateInfo create_info = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
  create_info.pApplicationInfo = &app_info;
  create_info.enabledExtensionCount = 0;
  create_info.ppEnabledExtensionNames = 0;
  create_info.enabledLayerCount = 0;
  create_info.ppEnabledLayerNames = 0;

  VkResult result = vkCreateInstance(&create_info, context.allocator, &context.instance);
  if (result != VK_SUCCESS)
  {
    KERROR("Failed to create Vulkan instance: %u", result);
    return FALSE;
  }

  KINFO("Vulkan renderer initialized succesfully");

  return TRUE;
}

void vulkan_renderer_backend_shutdown(renderer_backend *renderer_backend)
{
  // Destroy Vulkan device and instance
}

void vulkan_renderer_backend_on_resized(renderer_backend *renderer_backend, u16 width, u16 height)
{
  // Update Vulkan swapchain and re-create resources
}

b8 vulkan_renderer_backend_begin_frame(renderer_backend *renderer_backend, f32 delta_time)
{
  // Acquire new image from Vulkan swapchain
}

b8 vulkan_renderer_backend_end_frame(renderer_backend *renderer_backend, f32 delta_time)
{
  // Submit rendered commands to Vulkan command buffer and present the image
}