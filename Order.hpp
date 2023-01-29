//
// Created by Ishika Gupta on 12/7/21.
//


#ifndef FINALPROJECT_ORDER_HPP
#define FINALPROJECT_ORDER_HPP
#include <utility>
#include "Time.hpp"

/* The Order class represents an order of one or more food items placed by a customer.
 *  The order can be in one of three states: at the restaurant, out for delivery, or delivered.
 *  The order keeps track of the time it was placed,
 *  the information needed to cook and deliver it (food items and address),
 *  and the time taken to deliver it.
 */

class Order {
public:
    Order();
    Order(Time time, string info);
    void depart();
    void deliver(Time time);
    int getMinToDelivery();
    string toString();

private:
    Time time_created;
    Time time_delivered;
    string information;
    bool cooking_status;
};


// Pre: None
// Post: Creates an Order with default values for data members.
Order::Order() {
    cooking_status = false;
    information = "";
    time_created = Time();
    time_delivered = Time();
}

// Pre: None
// Post: Creates an order with the given order time and information.
Order::Order(Time t1, string info) {
    time_created = t1;
    time_delivered = Time();
    information = info;
    cooking_status = false;
}

// Pre: Order is at the restaurant.
// Post: Order is out for delivery.
void Order::depart() {
    //if already set to 1, throw logic_error;
    if (cooking_status) {
        throw logic_error("Already departed!");
    }
    cooking_status = true;
}

// Pre: Order is out for delivery.
// Post: Order is delivered. Time to delivery is recorded.
void Order::deliver(Time time) {
    if(!cooking_status) {
        throw logic_error("Order has not been started yet.");
    }
    time_delivered = time;
}

// Pre: Order is delivered.
// Post: Returns the minutes until the order is delivered
int Order::getMinToDelivery() {
    return Time::elapsedMin(time_created, time_delivered);
}

// Pre: None
// Post: Returns a string containing the order time and info.
string Order::toString() {
    string statement = " The order " + information;
    if (!cooking_status) {
        statement += " is still cooking.";
    }
    else {
        statement += " waiting to depart.";
    }
    return statement;
}

/*
// Pre: None
// Post: Returns time created
Time Order::getTimeCreated() {
    return time_created;
}
*/

#endif //FINALPROJECT_ORDER_HPP
