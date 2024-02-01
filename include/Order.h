#ifndef SIMUTRADEX_ORDER_H
#define SIMUTRADEX_ORDER_H
#include <string>
#include <utility>
#include <memory>


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

    bool operator<(const Order &order) const;
    bool operator>(const Order &order) const;
};

template<typename Compare>
struct OrderPtrCompare {
    Compare comp;

    explicit OrderPtrCompare(const Compare& comparator = Compare()) : comp(comparator) {}

    bool operator()(const std::shared_ptr<Order>& lhs, const std::shared_ptr<Order>& rhs) const {
        return comp(*lhs, *rhs);
    }
};



#endif //SIMUTRADEX_ORDER_H
