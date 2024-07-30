#include "asserts.h"
#include "logger.h"

#define TEXT_RED "\x1b[31m"
#define TEXT_GREEN "\x1b[32m"
#define TEXT_YELLOW "\x1b[33m"
#define TEXT_BLUE "\x1b[34m"
#define TEXT_PURPLE "\x1b[35m"
#define TEXT_CYAN "\x1b[36m"
#define TEXT_RESET_COLOR "\x1b[0m"

// constructor
Logger::Logger()
{
    // TODO: create log file
}

// destructor
Logger::~Logger()
{
    // TODO: clean up logging/write queued entries (for multi-threading)
}

std::string ColorizeText(const char *color, const char *text)
{
    std::string coloredText = color;
    coloredText.append(text).append(TEXT_RESET_COLOR);

    return coloredText;
}

using std::chrono::system_clock;

std::string Logger::CurrentTime()
{

    std::time_t now = system_clock::to_time_t(system_clock::now());

    std::string output{30, '\0'};
    std::strftime(&output[0], output.size(), "%H:%M:%S", std::localtime(&now));

    return output;
}

std::string LogHeader(const char *color, const char *type, bool filenameAndLine)
{
    std::string text("[");
    text.append(ColorizeText(color, type));
    text.append(Logger::CurrentTime());
    if(filenameAndLine)
    {
        text.append(color);
        text.append(" (file: ").append(__BASE_FILE__);
        text.append(")");
    }

    text.append(TEXT_RESET_COLOR);
    text.append("]: ");

    return text;
}

void Logger::LogToConsole(LogLevel logLevel, const char *msg)
{
    switch(logLevel)
    {
    case LogLevel::fatal:
        std::cout << LogHeader(TEXT_RED, "FATAL", true) << msg << std::endl;
        break;
    case LogLevel::error:
        std::cout << LogHeader(TEXT_PURPLE, "ERROR", true) << msg << std::endl;
        break;
    case LogLevel::warning:
        std::cout << LogHeader(TEXT_YELLOW, "WARN", true) << msg << std::endl;
        break;
    case LogLevel::info:
        std::cout << LogHeader(TEXT_BLUE, "INFO", false) << msg << std::endl;
        break;
    case LogLevel::debug:
        std::cout << LogHeader(TEXT_CYAN, "DEBUG", true) << msg << std::endl;
        break;
    case LogLevel::trace:
        std::cout << LogHeader(TEXT_GREEN, "TRACE", true) << msg << std::endl;
        break;
    default:
        break;
    }
}

void Logger::LogToFile(LogLevel logLevel, const char *msg, const char *filename)
{
}