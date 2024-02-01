#ifndef SIMUTRADEX_ORDERBOOK_H
#define SIMUTRADEX_ORDERBOOK_H

#include <memory>
#include <string>
#include <set>
#include <utility>
#include <queue>
#include <iostream>
#include <unordered_map>
#include "Logger.h"

enum Side {
    BUY,
    SELL
};

struct Order {
    std::string symbol;
    double price;
    double quantity;
    Side side;
    int id;

    Order(int id, std::string symbol, double price, double quantity, Side side) : id(id), symbol(std::move(symbol)),
                                                                                  price(price),
                                                                                  quantity(quantity), side(side) {}

    bool operator>(const Order &order) const {
        return this->price == order.price ? this->id < order.id : this->price > order.price;
    }
};


class OrderBook {
public:
    OrderBook() = default;

    void addOrder(const std::string &symbol, double price, double quantity, Side side);

    [[noreturn]] void runMatchingEngine();

    void matchOrder(const std::string &symbol);

    void showOrderBook(const std::string &symbol);

private:
    std::unordered_map<std::string, std::set<std::shared_ptr<Order>, std::greater<>>> bids;
    std::unordered_map<std::string, std::set<std::shared_ptr<Order>>> asks;
    std::queue<std::shared_ptr<Order>> orderQueue;
    std::atomic<int> idNum{0};
};

#endif //SIMUTRADEX_ORDERBOOK_H
