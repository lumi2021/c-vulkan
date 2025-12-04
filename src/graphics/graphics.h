#pragma once

#define GLFW_INCLUDE_VULKAN

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_vulkan.h>

#include <vulkan/vulkan_core.h>

bool graphics_init();
void graphics_deinit();

bool window_is_active();
void window_update();
void window_pool_events();
