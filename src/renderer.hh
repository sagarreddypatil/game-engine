#pragma once

#define VULKAN_HPP_NO_EXCEPTIONS
#define VULKAN_HPP_NO_SMART_HANDLE
#define VULKAN_HPP_ASSERT_ON_RESULT
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_handles.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <cstdlib>

#define panic { std::cerr
#define panic_end std::endl; assert(false); }

#ifndef NDEBUG
#define debug std::cout
#else
#define debug if (false) std::cout
#endif

class VulkanLow
{
  private:
    GLFWwindow *window;
    vk::Instance instance;

    vk::PhysicalDevice physical_device;
    vk::SurfaceKHR surface;

  public:
    VulkanLow(std::string title);
    void render_loop();
    ~VulkanLow();
};