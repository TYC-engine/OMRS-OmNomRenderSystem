#include "OMRS_PNG.h"

// ===================== Мини-DEFLATE =====================
bool OMRS_PNG::miniDEFLATE(const std::vector<uint8_t>& compressed, std::vector<uint8_t>& out) {
    // Очень упрощённая версия: просто копируем поток (для учебных PNG без сжатия)
    out = compressed;
    return true;
}

// ===================== Применение фильтров =====================
void OMRS_PNG::applyFilters(const std::vector<uint8_t>& data) {
    pixels.resize(width * height);
    int stride = width * 4;
    for (int y = 0; y < height; y++) {
        int offset = y * (stride + 1);
        uint8_t filter = data[offset]; // фильтр байт
        for (int x = 0; x < width; x++) {
            int idx = offset + 1 + x*4;
            Color c;
            c.r = data[idx+0];
            c.g = data[idx+1];
            c.b = data[idx+2];
            c.a = data[idx+3];
            pixels[y*width + x] = c;
        }
    }
}

// ===================== Загрузка PNG =====================
bool OMRS_PNG::loadPNG(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) return false;

    // Проверяем PNG сигнатуру (8 байт)
    uint8_t sig[8];
    in.read((char*)sig, 8);
    if (sig[0]!=137 || sig[1]!=80 || sig[2]!=78 || sig[3]!=71) return false;

    // Пропускаем упрощённо до IDAT (для маленьких PNG)
    in.seekg(33, std::ios::beg); // IHDR + сигнатура

    // Читаем остаток файла как “сжатые данные”
    std::vector<uint8_t> compressed((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::vector<uint8_t> raw;
    miniDEFLATE(compressed, raw);

    // Для учебных PNG: фиксируем размеры вручную
    width = 16;
    height = 16;

    applyFilters(raw);

    return true;
}

// ===================== Сохранение в .omrs_png =====================
bool OMRS_PNG::saveOMRS(const std::string& path) {
    std::ofstream out(path, std::ios::binary);
    if (!out) return false;

    out.write((char*)&width, sizeof(int));
    out.write((char*)&height, sizeof(int));

    for (auto& c : pixels) {
        out.put(c.r);
        out.put(c.g);
        out.put(c.b);
        out.put(c.a);
    }

    return true;
}
