#include <memory>
#include <string>
#include <set>
#include <utility>
#include <queue>
#include <iostream>
#include <unordered_map>

enum Side {
    BUY,
    SELL
};

struct Order {
    std::string symbol;
    double price;
    double quantity;
    Side side;

    Order(std::string symbol, double price, double quantity, Side side) : symbol(std::move(symbol)), price(price),
                                                                          quantity(quantity), side(side) {}

    bool operator>(const Order &order) const {
        return this->price == order.price ? this->quantity > order.quantity : this->price > order.price;
    }
};


class OrderBook {
public:
    OrderBook() = default;

    void addOrder(const std::string &symbol, double price, double quantity, Side side) {
        auto order = std::make_shared<Order>(Order(symbol, price, quantity, side));
        orderQueue.push(order);
        std::cout << "Added " << (side == BUY ? "BUY" : "SELL") << " order: Symbol=" << symbol
                  << ", Price=" << price << ", Quantity=" << quantity << std::endl;
    }


    [[noreturn]] void runMatchingEngine() {
        while (true) {
            if (orderQueue.empty()) {
//                std::cout << "Order queue is empty, waiting for new orders..." << std::endl;
                continue;
            }

            auto curOrder = orderQueue.front();
            orderQueue.pop();

            if (curOrder->side == Side::BUY) {
                bids[curOrder->symbol].insert(curOrder);
            } else {
                asks[curOrder->symbol].insert(curOrder);
            }

            matchOrder(curOrder->symbol);
        }
    }

    void matchOrder(const std::string &symbol) {
        while (!bids[symbol].empty() && !asks[symbol].empty()) {
            auto bid = *bids[symbol].begin();
            auto ask = *asks[symbol].begin();

            if (bid->price >= ask->price) {
                // Determine the quantity to be traded
                double tradeQuantity = std::min(bid->quantity, ask->quantity);
                std::cout << "Matching Orders: " << tradeQuantity << " units at price " << bid->price << std::endl;

                // Update the quantities of the bid and ask
                bid->quantity -= tradeQuantity;
                ask->quantity -= tradeQuantity;

                // Process the trade, e.g., record it, notify parties, etc. (not implemented here)

                // Remove the bid or ask from the book if its quantity is now zero
                if (bid->quantity == 0) {
                    std::cout << "Bid order fully matched and removed. Symbol=" << bid->symbol << std::endl;
                    bids.erase(bids.begin());
                }
                if (ask->quantity == 0) {
                    std::cout << "Ask order fully matched and removed. Symbol=" << ask->symbol << std::endl;
                    asks.erase(asks.begin());
                }
            }
        }
    }

private:
    std::unordered_map<std::string, std::set<std::shared_ptr<Order>, std::greater<>>> bids;
    std::unordered_map<std::string, std::set<std::shared_ptr<Order>>> asks;
    std::queue<std::shared_ptr<Order>> orderQueue;

};

