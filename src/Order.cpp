#include "Order.h"

bool Order::operator<(const Order &order) const {
    return this->price == order.price ? this->id > order.id : this->price < order.price;
}

bool Order::operator>(const Order &order) const {
    return this->price == order.price ? this->id < order.id : this->price > order.price;
}

