#include <iostream>
#include <thread>
#include "OrderBook.h"
#include "Logger.h"

int main() {
    OrderBook orderBook;

    // Run the matching engine in a separate thread
    std::thread matchingEngineThread(&OrderBook::runMatchingEngine, &orderBook);

    while (true) {
        std::string symbol;
        double price, quantity;
        int sideInt;
        Side side;

        logger.log("Enter order details (symbol, price, quantity, side(0 for BUY, 1 for SELL)) or 'exit' to quit:");
        std::cin >> symbol;

        if (symbol == "exit") {
            exit(0);
        }

        std::cin >> price >> quantity >> sideInt;
        side = (sideInt == 0) ? Side::BUY : Side::SELL;

        orderBook.addOrder(symbol, price, quantity, side);
    }

    matchingEngineThread.join();

    return 0;
}
