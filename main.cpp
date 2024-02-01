#include <iostream>
#include <thread>
#include "OrderBook.h"
#include "Logger.h"

void printHelp() {
    logger.log("Available commands:");
    logger.log("-h                 Show this help message.");
    logger.log("show [symbol]      Show the order book for the specified symbol.");
    logger.log("exit               Exit the program.");
}

int main() {
    OrderBook orderBook;

    // Run the matching engine in a separate thread
    std::thread matchingEngineThread(&OrderBook::runMatchingEngine, &orderBook);
    logger.log("Enter '-h' for help. Enter 'show [symbol]' to display orders for a symbol.");

    while (true) {
        std::string symbol;
        double price, quantity;
        int sideInt;
        Side side;

        logger.log("Enter order details (symbol, price, quantity, side(0 for BUY, 1 for SELL)) or 'exit' to quit:");
        std::cin >> symbol;

        if (symbol == "-h") {
            printHelp();
            continue;
        } else if (symbol == "show") {
            std::cin >> symbol;
            orderBook.showOrderBook(symbol);
            continue;
        } else if (symbol == "exit") {
            logger.log("Exiting program.");
            exit(0);
        }

        std::cin >> price >> quantity >> sideInt;
        side = (sideInt == 0) ? Side::BUY : Side::SELL;

        orderBook.addOrder(symbol, price, quantity, side);
    }

    matchingEngineThread.join();

    return 0;
}
