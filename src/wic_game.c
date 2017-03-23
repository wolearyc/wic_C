/* ----------------------------------------------------------------------------
 * wic - a simple 2D game engine for Mac OSX written in C
 * Copyright (C) 2013-2017  Willis O'Leary
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 * File:    wic_game.c
 * ----------------------------------------------------------------------------
 */
#include "wic_game.h"
const unsigned WIC_GAME_CONTINUE = 1;
const unsigned WIC_GAME_TERMINATE = 2;
static bool wic_focus = false;
static bool wic_down_keys[360] = {0};
static bool wic_pressed_keys[360] = {0};
static unsigned char wic_input[100] = {0};
static WicPair wic_cursor_location = {0.0,0.0};
static WicPair wic_scroll_offset = {0.0,0.0};
void wic_reset_input()
{
    memset(wic_pressed_keys, 0, sizeof(wic_down_keys));
    memset(wic_input, 0, sizeof(wic_input));
    wic_scroll_offset = (WicPair) {0,0};
}
void wic_error_callback(int error, const char* description)
{
    wic_throw_error(WIC_ERRNO_GLFW_FAIL);
}
void wic_focus_callback(GLFWwindow* window, int n)
{
    wic_focus = (bool) n;
}
void wic_key_callback(GLFWwindow* window, int key, int scancode, int action,
                      int mods)
{
    if(wic_focus && key < 360)
    {
        if(action == GLFW_RELEASE)
            wic_down_keys[key] = false;
        else if(action == GLFW_PRESS)
        {
            wic_down_keys[key] = true;
            wic_pressed_keys[key] = true;
        }
    }
}
void wic_char_callback(GLFWwindow* window, unsigned int key)
{
    if(wic_focus)
    {
        int startIndex = 0;
        while(startIndex < 100 && wic_input[startIndex] != 0)
            startIndex++;
        if(startIndex != 99)
            wic_input[startIndex] = (unsigned char) key;
    }
}
void wic_cursor_location_callback(GLFWwindow* window, double x, double y)
{
    if(wic_focus)
    {
        wic_cursor_location.x = x;
        wic_cursor_location.y = y;
    }
}
void wic_mouse_button_callback(GLFWwindow* window, int button, int action,
                               int mods)
{
    if(wic_focus)
    {
        if(action == GLFW_PRESS)
            wic_down_keys[button + 350] = true;
        else
            wic_down_keys[button + 350] = false;
    }
}
void wic_scroll_callback(GLFWwindow* window, double x, double y)
{
    if(wic_focus)
    {
        wic_scroll_offset.x = x;
        wic_scroll_offset.y = y;
    }
}
static bool wic_initialized = false;
struct WicGame
{
    GLFWwindow* window;
    WicPair dimensions;
    WicPair pixel_density;
    double seconds_per_frame;
    double previous_time;
    double delta;
    FT_Library freetype_library;

};
WicGame* wic_init_game(const char* title, WicPair dimensions, unsigned fps,
                       bool resizeable, bool fullscreen, unsigned samples)
{
    if(wic_initialized)
        return (void*) wic_throw_error(WIC_ERRNO_ALREADY_INIT);
    if(!title)
        return (void*) wic_throw_error(WIC_ERRNO_NULL_TITLE);
    if(!strlen(title))
        return (void*) wic_throw_error(WIC_ERRNO_SMALL_TITLE);
    if(dimensions.x < 32)
        return (void*) wic_throw_error(WIC_ERRNO_SMALL_X_DIMENSION);
    if(dimensions.y < 32)
        return (void*) wic_throw_error(WIC_ERRNO_SMALL_Y_DIMENSION);
    if(!fps)
        return (void*) wic_throw_error(WIC_ERRNO_SMALL_FPS);
    if(!glfwInit())
        return (void*) wic_throw_error(WIC_ERRNO_GLFW_FAIL);
    glfwWindowHint(GLFW_REFRESH_RATE, fps);
    glfwWindowHint(GLFW_SAMPLES, samples);
    glfwWindowHint(GLFW_RESIZABLE, resizeable);
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if(!monitor)
    {
        glfwTerminate();
        return (void*) wic_throw_error(WIC_ERRNO_MONITOR_FAIL);
    }
    GLFWwindow* window;
    if(fullscreen)
        window = glfwCreateWindow(dimensions.x, dimensions.y, title, monitor,
                                  0);
    else
        window = glfwCreateWindow(dimensions.x, dimensions.y, title, 0, 0);
    if(!window)
    {
        glfwTerminate();
        return (void*) wic_throw_error(WIC_ERRNO_WINDOW_FAIL);
    }
    glfwSetErrorCallback(wic_error_callback);
    glfwSetWindowFocusCallback(window, wic_focus_callback);
    glfwSetKeyCallback(window, wic_key_callback);
    glfwSetCharCallback(window, wic_char_callback);
    glfwSetCursorPosCallback(window, wic_cursor_location_callback);
    glfwSetScrollCallback(window, wic_scroll_callback);
    glfwMakeContextCurrent(window);
    glfwSetTime(0.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    FT_Library freetype_library;
    int error = FT_Init_FreeType(&freetype_library);
    if(error != 0)
    {
        glfwTerminate();
        glfwDestroyWindow(window);
        return (void*) wic_throw_error(WIC_ERRNO_FREETYPE_FAIL);
    }
    int physicalWidth; int physicalHeight;
    glfwGetMonitorPhysicalSize(monitor, &physicalWidth, &physicalHeight);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    WicGame* result = malloc(sizeof(WicGame));
    if(!result)
    {
        glfwTerminate();
        glfwDestroyWindow(window);
        return (void*) wic_throw_error(WIC_ERRNO_NO_HEAP);
    }
    result->window = window;
    result->dimensions = dimensions;
    result->pixel_density =(WicPair) {mode->width / (physicalWidth * 0.0393701),
                                 mode->height / (physicalHeight * 0.0393701)};
    result->seconds_per_frame = 1.0 / fps;
    result->previous_time = 0.0;
    result->delta = 0.0;
    result->freetype_library = freetype_library;
    wic_initialized = true;
    return result;
}
unsigned wic_updt_game(WicGame* target)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    if(!glfwWindowShouldClose(target->window))
    {
        float delay = target->seconds_per_frame -
                       (glfwGetTime() - target->previous_time);
        if(delay > 0)
            usleep(delay * 1000);
        wic_reset_input();
        glfwSwapBuffers(target->window);
        glFlush();
        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        target->delta = glfwGetTime() - target->previous_time;
        target->previous_time = glfwGetTime();
        glfwPollEvents();
        return WIC_GAME_CONTINUE;
    }
    return WIC_GAME_TERMINATE;
}
bool wic_exit_game(WicGame* target)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    glfwSetWindowShouldClose(target->window, true);
    return true;
}
double wic_get_delta(WicGame* target)
{
    if(!target)
    {
        wic_throw_error(WIC_ERRNO_NULL_TARGET);
        return -1;
    }
    return target->delta;
}
bool wic_free_game(WicGame* target)
{
    if(!target)
        return wic_throw_error(WIC_ERRNO_NULL_TARGET);
    glfwDestroyWindow(target->window);
    glfwTerminate();
    
    target->window = 0;
    target->dimensions = (WicPair) {0,0};
    target->seconds_per_frame = 0.0;
    target->previous_time = 0.0;
    target->pixel_density = (WicPair) {0,0};
    wic_initialized = false;
    return true;
}
bool wic_is_key_down(enum WicKey key)
{
    return wic_down_keys[(int) key];
}
bool wic_is_key_pressed(enum WicKey key)
{
    return wic_pressed_keys[(int) key];
}
unsigned char* wic_get_input()
{
    return wic_input;
}
WicPair wic_get_cursor_location(WicGame* game)
{
    WicPair result = wic_cursor_location;
    result.y = game->dimensions.y - result.y;
    return result;
}
WicPair wic_get_scroll_offset()
{
    return wic_scroll_offset;
}
double wic_get_time()
{
    return glfwGetTime();
}
WicPair wic_convert_location(WicPair location, WicPair dimensions)
{
    WicPair result = wic_multiply_pairs(location, (WicPair) {2,2});
    result = wic_divide_pairs(result, dimensions);
    return wic_subtract_pairs(result, (WicPair) {1,1});
}
