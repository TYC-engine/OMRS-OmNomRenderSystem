#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include <iostream>

struct Color { uint8_t r, g, b, a; };

class OMRS_PNG {
public:
    int width = 0;
    int height = 0;
    std::vector<Color> pixels;

    // Загружаем PNG с минимальной распаковкой DEFLATE
    bool loadPNG(const std::string& path);

    // Сохраняем в свой формат .omrs_png
    bool saveOMRS(const std::string& path);

private:
    // Мини-DEFLATE: читает последовательные байты (только для учебных PNG)
    bool miniDEFLATE(const std::vector<uint8_t>& compressed, std::vector<uint8_t>& out);

    // Применяем простые PNG фильтры (None/Sub/Up)
    void applyFilters(const std::vector<uint8_t>& data);
};
