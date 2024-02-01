#ifndef SIMUTRADEX_LOGGER_H
#define SIMUTRADEX_LOGGER_H

#include <string>
#include <mutex>
#include <sstream>
#include <thread>
#include <iostream>
#include <atomic>
#include "ThreadSafeQueue.h"


class Logger {
public:
    Logger();

    ~Logger();

    void log(const std::string& message) ;

private:
    void process_log_queue();

    ThreadSafeQueue<std::string> log_queue{};
    std::thread logger_thread;
    std::atomic<bool> exit_flag;
};

extern Logger logger;

#endif //SIMUTRADEX_LOGGER_H
