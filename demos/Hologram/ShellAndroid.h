#ifndef SHELL_ANDROID_H
#define SHELL_ANDROID_H

#include <android_native_app_glue.h>
#include "Shell.h"

class ShellAndroid : public Shell {
public:
    ShellAndroid(android_app &app, Game &game);
    ~ShellAndroid();

    void log(LogPriority priority, const char *msg);

    void run();
    void quit();

private:
    PFN_vkGetInstanceProcAddr load_vk();
    bool can_present(VkPhysicalDevice phy, uint32_t queue_family) { return true; }

    VkSurfaceKHR create_surface(VkInstance instance);

    void on_app_cmd(int32_t cmd);
    int32_t on_input_event(const AInputEvent *event);

    static inline void on_app_cmd(android_app *app, int32_t cmd);
    static inline int32_t on_input_event(android_app *app, AInputEvent *event);

    android_app &app_;

    void *lib_handle_;
};

void ShellAndroid::on_app_cmd(android_app *app, int32_t cmd)
{
    auto android = reinterpret_cast<ShellAndroid *>(app->userData);
    android->on_app_cmd(cmd);
}

int32_t ShellAndroid::on_input_event(android_app *app, AInputEvent *event)
{
    auto android = reinterpret_cast<ShellAndroid *>(app->userData);
    return android->on_input_event(event);
}

#endif // SHELL_ANDROID_H