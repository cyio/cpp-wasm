#include <emscripten.h>
#include <stdint.h>
#include <algorithm> // Include this header for std::min
#include <cstdint>   // Include this header for uint8_t
#include <nlohmann/json.hpp>

extern "C" {

// 分配和释放内存的函数已经由 Emscripten 提供，因此不需要实现。

// 一个简单的图像处理函数：增加亮度
EMSCRIPTEN_KEEPALIVE
char* processImage(uint8_t* img, int width, int height, int brightness_increase) {
    nlohmann::json j;
    
    int num_pixels = width * height;
    for (int i = 0; i < num_pixels * 4; i += 4) {
        // 增加 RGB 的值，忽略 alpha
        img[i] = (uint8_t) std::min(255, img[i] + brightness_increase);
        img[i+1] = (uint8_t) std::min(255, img[i+1] + brightness_increase);
        img[i+2] = (uint8_t) std::min(255, img[i+2] + brightness_increase);
    }

    j["error"] = 0;
    // 将 JSON 对象转换为字符串
    std::string result_str = j.dump();

    // 使用 strdup 分配一个新的字符串，这将在 WebAssembly 的堆中
    return strdup(result_str.c_str());
}

}