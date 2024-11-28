#include "renderer.hh"

int main()
{
    VulkanLow renderer("Vulkan Low");
    renderer.render_loop();
    return 0;
}
