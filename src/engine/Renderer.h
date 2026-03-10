// Renderer.h
#pragma once
#include <vector>
#include <string>
#include <random>
#include <iostream>

struct Color {
    unsigned char r, g, b, a;
};

class Renderer {
public:
    int width, height;
    std::vector<Color> pixels;

    Renderer() : width(0), height(0) {}

    // Загрузка PNG через stb_image
    bool loadImage(const std::string& path);

    // Инициализация буфера
    void init();

    // Получаем все пиксели
    std::vector<int> allPixels();

    // Меняем цвет пикселя по индексу
    void changeColor(int index, Color c);

    // Отрисовка в консоль (ASCII)
    void renderConsole();

    // Генератор случайного цвета
    Color randomColor();
};
