#include "renderer.hh"
#include <cstdint>
#include <expected>

GLFWwindow *create_window(std::string title)
{
    if (!glfwInit())
    {
        panic << "failed to initialize GLFW" << panic_end;
    }

    debug << "GLFW version: " << glfwGetVersionString() << std::endl;

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(800, 600, title.c_str(), nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        panic << "failed to create window" << panic_end;
    }

    return window;
}

vk::Instance vk_create_instance(std::string title)
{
    const auto [res0, supported_exts] = vk::enumerateInstanceExtensionProperties();
    if (res0 != vk::Result::eSuccess)
        panic << "failed to enumerate instance extensions" << panic_end;

    const auto [res1, supported_layers] = vk::enumerateInstanceLayerProperties();
    if (res1 != vk::Result::eSuccess)
        panic << "failed to enumerate instance layers" << panic_end;

    vk::ApplicationInfo app_info{};
    app_info.pApplicationName = title.c_str();
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "No Engine";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

    vk::InstanceCreateInfo create_info{};
    create_info.pApplicationInfo = &app_info;
    create_info.enabledLayerCount = 0;

    if (!glfwVulkanSupported())
        panic << "glfw vulkan not supported" << panic_end;

    uint32_t glfw_ext_count;
    const char **glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

    if (glfw_exts == nullptr)
        panic << "failed to get glfw required instance extensions" << panic_end;

    std::vector<const char *> exts(glfw_exts, glfw_exts + glfw_ext_count);
    exts.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    exts.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

    debug << "loading instance extensions:" << std::endl;
    for (auto ext : exts)
    {
        debug << "\t" << ext << std::endl;
        if (std::find_if(supported_exts.begin(), supported_exts.end(),
                         [ext](auto &e) { return std::string(e.extensionName) == ext; }) == supported_exts.end())
            panic << "extension " << ext << " not supported" << panic_end;
    }

    create_info.setFlags(vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR);
    create_info.setPEnabledExtensionNames(exts);

    auto [res2, instance] = vk::createInstance(create_info);
    if (res2 != vk::Result::eSuccess) {
        panic << "failed to create instance: " << vk::to_string(res2) << panic_end;
    }

    return instance;
}

VulkanLow::VulkanLow(std::string title)
{
    window = create_window(title);
    instance = vk_create_instance(title);
}

void VulkanLow::render_loop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}

VulkanLow::~VulkanLow()
{
    instance.destroy();
    glfwDestroyWindow(window);
    glfwTerminate();
}
