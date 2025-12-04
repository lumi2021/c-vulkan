#include "global.h"
#include "graphics/graphics.h"

int main(int argc, char const *argv[])
{
    printf("Hello, World!\n");
    printf("Initializing engine...\n");
    
    if (!graphics_init()) return 1;
    
    while (window_is_active()) {
        window_pool_events();

        window_update();
    }

    graphics_deinit();
    
    printf("Goodbye, World\n");
    return 0;
}
