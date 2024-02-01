#ifndef SIMUTRADEX_ORDERBOOK_H
#define SIMUTRADEX_ORDERBOOK_H

#include <set>
#include <queue>
#include <unordered_map>
#include "Logger.h"
#include "Order.h"

class OrderBook {
public:
    OrderBook() = default;

    void addOrder(const std::string &symbol, double price, double quantity, Side side);

    [[noreturn]] void runMatchingEngine();

    void matchOrder(const std::string &symbol);

    void showOrderBook(const std::string &symbol);

private:
    std::unordered_map<std::string, std::set<std::shared_ptr<Order>, OrderPtrCompare<std::greater<>>>> bids;
    std::unordered_map<std::string, std::set<std::shared_ptr<Order>, OrderPtrCompare<std::less<>>>> asks;
    std::queue<std::shared_ptr<Order>> orderQueue;
    std::atomic<int> idNum{0};
};

#endif //SIMUTRADEX_ORDERBOOK_H
