#pragma once

#include "defines.h"

// TODO: temporary. (will be obscured by platform layer)
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// disable debug && trace if release version
#if IRELEASE == 1
    #define LOG_DEBUG_ENABLED 0
    #define LOG_TRACE_ENABLED 0
#endif

enum class LogLevel
{
    fatal = 0,
    error = 1,
    warning = 2,
    info = 3,
    debug = 4,
    trace = 5
};

class Logger
{
    public:
    Logger();
    ~Logger();

    static std::string CurrentTime();

    IAPI static void LogToConsole(LogLevel logLevel, const char *msg);
    IAPI static void LogToFile(LogLevel logLevel, const char *msg, const char *filename);
};
