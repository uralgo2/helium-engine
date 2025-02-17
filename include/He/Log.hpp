#ifndef HELIUM_LOG_HPP
#define HELIUM_LOG_HPP

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

namespace He::Log {
    #define LOG_WARN(...) {\
        fmt::print("[LOG] {:%H:%M:%S} ", std::chrono::system_clock::now());\
    fmt::print(fmt::fg(fmt::color::yellow), "WARN! ");\
    fmt::println(__VA_ARGS__);\
    }
    #define LOG_ERROR(...) {\
        fmt::print("[LOG] {:%H:%M:%S} ", std::chrono::system_clock::now());\
    fmt::print(fmt::fg(fmt::color::red), "ERROR! ");\
    fmt::println(__VA_ARGS__);\
    }
    #define LOG_INFO(...) {\
        fmt::print("[LOG] {:%H:%M:%S} ", std::chrono::system_clock::now());\
    fmt::print("INFO: ");\
    fmt::println(__VA_ARGS__);\
    }

    #ifdef _DEBUG
    #define DEBUG_WARN(...) {\
        fmt::print("[DEBUG] {:%H:%M:%S} ", std::chrono::system_clock::now());\
    fmt::print(fmt::fg(fmt::color::yellow), "WARN! ");\
    fmt::println(__VA_ARGS__);\
    }
    #define DEBUG_ERROR(...) {\
        fmt::print("[DEBUG] {:%H:%M:%S} ", std::chrono::system_clock::now());\
    fmt::print(fmt::fg(fmt::color::red), "ERROR! ");\
    fmt::println(__VA_ARGS__);\
    }
    #define DEBUG_INFO(...) {\
        fmt::print("[DEBUG] {:%H:%M:%S} ", std::chrono::system_clock::now());\
    fmt::print("INFO: ");\
    fmt::println(__VA_ARGS__);\
    }
    #else
    #define DEBUG_WARN(...)
    #define DEBUG_ERROR(...)
    #define DEBUG_INFO(...)
    #endif
}

#endif
