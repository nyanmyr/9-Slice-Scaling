#include "../Headers/Scenes.hpp"
#include "../Headers/Config.hpp"
#include <stdexcept>

void playScene(Scene scene) {
    switch (scene) {
    case Scene::START:
        startScene();
        break;
    default:
        throw std::runtime_error("Scene does not exist.");
        break;
    }

    Asset::window().close();
}
