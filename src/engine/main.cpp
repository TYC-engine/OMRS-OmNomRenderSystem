#include "Renderer.h"

int main() {
    Renderer engine;

    if (!engine.loadImage("assets/icon.png")) return 1;

    engine.init();

    auto pixels = engine.allPixels();

    // Генерация случайного цвета
    Renderer::Color random = engine.randomColor();

    // Меняем цвет первых 1600 пикселей (или меньше, если меньше пикселей)
    for (int i : pixels) {
        if (i >= 1 && i <= 1600)
            engine.changeColor(i, random);
    }

    engine.renderConsole();

    return 0;
}
