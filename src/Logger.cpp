#include "Logger.h"


Logger::Logger() : exit_flag(false) {
    logger_thread = std::thread(&Logger::process_log_queue, this);
}


Logger::~Logger() {
    exit_flag = true;
    log_queue.push("Logger Exiting"); // Trigger exit
    logger_thread.join();
}

void Logger::log(const std::string &message) {
    log_queue.push(message);
}

void Logger::process_log_queue() {
    std::string message;
    while (!exit_flag) {
        log_queue.wait_and_pop(message);
        if (exit_flag) break;
        std::cout << message << std::endl;
    }
}

Logger logger;