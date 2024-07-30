#include "logger.h"

int main()
{
    // NOTE: mutex lock doesn't work all that well with output streams...
    // therefore this logger is thread UNSAFE (for now)

    // ---------------- basics -------------

    Log(LOG_INFO) << "HELLO WORLD\n";

    Log.SetLogLevel(LOG_WARN);

    Log(LOG_INFO) << "this should not show\n";
    Log(LOG_WARN, FILE_INFO) << "this should show\n";

    // ---------------- files -------------
    Log.EnableFileOutput("log.ini");

    Log(LOG_ERROR) << "hello world\n";
    Log(LOG_WARN) << "warning man\n";
    Log(LOG_FATAL, FILE_INFO) << "fatal error bruh...\n";

    Log.DisableFileOutput();

    // --------------- ways to log --------
    Log.SetLogLevel(LOG_INFO);

    Log(LOG_INFO) << "normal log with LOG_INFO macro\n";

    Log(LogLevel::DEBUG) << "normal log using log level enum\n";

    Log(LOG_WARN, FILE_INFO) << "log with file info (file:line)\n";

    LOG(LOG_INFO, "logger macro " << "for less verbosity and auto file info\n");
    LOG(LOG_INFO, "think of it as a macro, within a macro.. within a macro.\n");
}