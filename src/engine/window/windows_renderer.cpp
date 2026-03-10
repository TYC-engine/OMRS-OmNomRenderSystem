#include <windows.h>
#include <vector>
#include <cstdint>

struct Color { uint8_t r,g,b,a; };

int width = 640;
int height = 480;
std::vector<Color> buffer(width*height);

// ========================== WinAPI ==========================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_DESTROY: PostQuitMessage(0); break;
        default: return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// ========================== Рисуем буфер ==========================
void drawBuffer(HDC hdc) {
    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    StretchDIBits(hdc, 0, 0, width, height, 0, 0, width, height,
                  buffer.data(), &bmi, DIB_RGB_COLORS, SRCCOPY);
}

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "OMRS_Window";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, "OMRS_Window", "OMRSM Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);

    // ========================== Генерация тестовой картинки ==========================
    for(int y=0;y<height;y++)
        for(int x=0;x<width;x++)
            buffer[y*width+x] = { (uint8_t)(x%256), (uint8_t)(y%256), 128, 255 };

    MSG msg = {};
    while(true) {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if(msg.message==WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        HDC hdc = GetDC(hwnd);
        drawBuffer(hdc);
        ReleaseDC(hwnd, hdc);
    }

    return 0;
}
