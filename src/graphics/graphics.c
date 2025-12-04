#include "../global.h"
#include <SDL3/SDL_vulkan.h>
#include <stdint.h>
#include <stdio.h>
#include "graphics.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

static SDL_Window *window;
static SDL_Surface *surface;

static VkInstance instance;

static bool window_running = false;

void glfw_error_callback(int code, const char* desc) {
    fprintf(stderr, "GLFW error %d: %s\n", code, desc);
}


bool vulkan_create_instance() {
    VkApplicationInfo appInfo;

    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    appInfo.pNext = 0;

    uint32_t extensionCount = 0;
    const char *const *extensions;
    extensions = SDL_Vulkan_GetInstanceExtensions(&extensionCount);

    VkInstanceCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = extensionCount;
    createInfo.ppEnabledExtensionNames = extensions;
    createInfo.enabledLayerCount = 0;
    createInfo.flags = 0;
    createInfo.pNext = 0;

    if (vkCreateInstance(&createInfo, null, &instance) != VK_SUCCESS) {
        printf("ERROR: failed to create instance!");
        return false;
    }

    return true;
}


bool init_window() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {

        printf("ERROR: failed to initialize SDL3\n");
        return false;
    }

    window = SDL_CreateWindow("Vulkan window",WIDTH, HEIGHT,
        SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("ERROR: Failed to initialize window\n");
        return false;
    }
    
    surface = SDL_GetWindowSurface(window);
    if (!surface) {
        printf("ERROR: Failed to get window surface\n");
        return false;
    }
    
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, null);
    
    printf("%i extensions supported\n", extensionCount);
    
    window_running = true;
    return true;
}
void deinit_window() {
    SDL_DestroyWindow(window);
    SDL_Quit();
    window = null;
}

bool init_graphics_api() {
    if (!vulkan_create_instance()) return false;
    return true;
}
void deinit_graphics_api() {

}


bool graphics_init() {

    printf("Initializing window...\n");
    if (!init_window())
    {
        printf("ERROR: Cannot initialize window!\n");
        return false;
    }
    printf("Window initialized\n");

    printf("Initializing graphics API...\n");
    if (!init_graphics_api())
    {
        printf("ERROR: Cannot initialize graphics API!\n");
        return false;
    }
    printf("graphics API initialized\n");

    return true;
}
void graphics_deinit() {
    deinit_graphics_api();
    deinit_window();
}

bool window_is_active() {
    return window_running;
}
void window_update() {
    SDL_UpdateWindowSurface(window);
}
void window_pool_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) window_running = false;
    }
}
