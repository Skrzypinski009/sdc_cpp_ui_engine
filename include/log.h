#pragma once

#include <string>

#include "color.h"

class Log {
public:

    static int log_mode;

    typedef enum {
        INFO = 1,
        WARNING = 2,
        ERROR = 4
    } LogMode;

    static void print(const char*); 
    static void print(const std::string);
    static void print(const int); 
    static void print(const float);
    static void print(const Color);

    static void info(const char*);
    static void warning(const char*);
    static void error(const char*);
};