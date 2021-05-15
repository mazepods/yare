#include <core/app.h>

int main(int argc, char const *argv[]) {
    app_config config;
    config.x = 0;
    config.y = 0;
    config.width = 640;
    config.height = 480;
    config.name = "Yare Engine";

    app_create(&config);
    app_run();

    return 0;
}