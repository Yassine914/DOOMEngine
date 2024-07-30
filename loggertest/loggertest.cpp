#include "logger.h"

int main()
{
    Log(LOG_INFO) << "HELLO WORLD\n";

    Log.SetLogLevel(LOG_WARN);

    Log(LOG_INFO) << "this should not show\n";
    Log(LOG_WARN, FILE_INFO) << "this should show\n";

    // ---------------- files -------------
    Log.EnableFileOutput("log.ini");

    Log(LOG_ERROR) << "hello world\n";
    Log(LOG_WARN) << "warning man\n";
    Log(LOG_FATAL, FILE_INFO) << "fatal error bruh...\n";
}