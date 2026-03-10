// Renderer.cpp
#include "Renderer.h"
#include "stb_image.h"

bool Renderer::loadImage(const std::string& path) {
    int channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
    if (!data) {
        std::cerr << "Failed to load image: " << stbi_failure_reason() << std::endl;
        return false;
    }

    pixels.resize(width * height);
    for (int i = 0; i < width * height; i++) {
        pixels[i].r = data[i * 4 + 0];
        pixels[i].g = data[i * 4 + 1];
        pixels[i].b = data[i * 4 + 2];
        pixels[i].a = data[i * 4 + 3];
    }

    stbi_image_free(data);
    return true;
}

void Renderer::init() {
    std::cout << "Renderer initialized (" << width << "x" << height << ")\n";
}

std::vector<int> Renderer::allPixels() {
    std::vector<int> indices;
    for (int i = 0; i < width * height; i++)
        indices.push_back(i);
    return indices;
}

void Renderer::changeColor(int index, Color c) {
    if (index >= 0 && index < (int)pixels.size())
        pixels[index] = c;
}

Renderer::Color Renderer::randomColor() {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> dist(0, 255);
    return { (unsigned char)dist(rng), (unsigned char)dist(rng), (unsigned char)dist(rng), 255 };
}

void Renderer::renderConsole() {
    for (int y = 0; y < height; y += 2) { // пропускаем строки для пропорции
        for (int x = 0; x < width; x++) {
            Color c = pixels[y * width + x];
            int brightness = (c.r + c.g + c.b) / 3;
            if (brightness < 64) std::cout << "#";
            else if (brightness < 128) std::cout << "*";
            else if (brightness < 192) std::cout << "+";
            else std::cout << ".";
        }
        std::cout << "\n";
    }
}
