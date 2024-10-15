#include "log.h"

#include <iostream>
#include <string>
#include <stdio.h>

int Log::log_mode = Log::LogMode::INFO | Log::LogMode::WARNING | Log::LogMode::ERROR;

void Log::print(const char* char_str) {
    std::cout << char_str << std::endl;
}

void Log::print(const std::string str) {
    std::cout << str << std::endl;
}

void Log::print(const int i) {
    std::cout << i << std::endl;
}

void Log::print(const float f) {
    std::cout << f << std::endl;
}

void Log::print(const Color c) {
    std::cout << "(" << (int)c.r << ", ";
    std::cout << (int)c.g << ", ";
    std::cout << (int)c.b << ", ";
    std::cout << (int)c.a << ")" << std::endl;
}

void Log::info(const char* char_str) {
    if (Log::log_mode & Log::LogMode::INFO)
        std::cout << "\033[0;36m[INFO]\033[0m " << char_str << std::endl;
}

void Log::warning(const char* char_str) {
    if (Log::log_mode & Log::LogMode::WARNING)
        std::cout << "\033[0;33m[WARNING]\033[0m " << char_str << std::endl;
}

void Log::error(const char* char_str) {
    if (Log::log_mode & Log::LogMode::ERROR)
        std::cout << "\033[0;31m[ERROR]\033[0m " << char_str << std::endl;
}


