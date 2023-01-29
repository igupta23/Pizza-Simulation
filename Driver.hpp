//
// Created by Ishika Gupta on 12/7/21.
//

#ifndef FINALPROJECT_DRIVER_HPP
#define FINALPROJECT_DRIVER_HPP

#include <string>
#include <queue>
#include "Time.hpp"
#include "Order.hpp"
using namespace std;

/** The Driver class represents a pizza delivery driver.
 *  The driver can be in one of several states: not logged in, logged in and at the restaurant,
 *  delivering (i.e., on the way to a delivery), and driving (i.e., on the way back from a delivery). The driver keeps track of its own stats
 *  (time delivering, time driving, tips, and number of deliveries).
 *  If the driver is currently delivering an order, the driver stores the order.
 */

class Driver{
private:
    string name;
    Time timeDeparted, timeArrived, timeDelivered;
    Order* order;
    float totalTip;
    bool loggedIn;
    bool driving;
    bool delivering;
    int totalDeliveries;



public:
    Driver(string newName); //implemented
    void login(); //implemented
    void logout(); //implemented
    void depart(Time time, Order* orders); //implemented
    void deliver(Time time, float tip); //implemented
    void arrive(Time time); //implemented
    string getName() const; //implemented
    bool loggedInCheck(); //implemented
    int getTotalDeliveries(); //implemented
    int getTotalMinDelivering(); //implemented
    int getTotalMinDriving(); //implemented
    float getTotalTips(); //implemented
    Order* getOrder(); //implemented
    string toString(); //implemented
};


// Pre: None
// Post: Creates a logged-in driver with the given name
Driver::Driver(string driverName) {
    name = driverName;
    totalTip = 0;
    totalDeliveries = 0;
}

// Pre: Driver is not logged in.
// Post: Logs the driver in
void Driver::login() {
    loggedIn = true;
}

// Pre: Driver is logged in and at the restaurant.
// Post: Logs the driver out.
void Driver::logout() {
    if (loggedIn && !driving && !delivering){
        loggedIn = false;
    }
}

// Pre: None
// Post: Returns true if and only if the driver is logged in.
bool Driver::loggedInCheck(){
    return loggedIn;
}

// Pre: None
// Post: Returns the total number of completed deliveries.
int Driver::getTotalDeliveries() {
    return totalDeliveries;
}

// Pre: None
// Post: Returns the total tips received, in dollars.
float Driver::getTotalTips() {
    return totalTip;
}

// Pre: Driver is delivering.
// Post: Returns the order being delivered.
Order* Driver::getOrder() {
    return order;
}

// Pre: Driver is logged in and at the restaurant.
// post: Driver is delivering. Departure time is recorded.
void Driver::depart(Time time, Order* orders) {
    timeDeparted = time;
    order = orders;
    driving = true;
    delivering = true;
}

// Pre: Driver is delivering, tip >= 0.
// Post: Driver is not delivering. Driver’s stats are updated.
void Driver::deliver(Time time, float tip) {
    totalTip += tip;
    timeDelivered = time;
    delivering = false;
    driving = true;
    totalDeliveries++;
}

// Pre: Driver is driving but not delivering.
// Post: Driver is at the restaurant. Driver’s stats are updated.
void Driver::arrive(Time time) {
    timeArrived = time;
    driving = false;
}

// Pre: None
// Post: Returns the driver’s name.
string Driver::getName() const {
    return name;
}

// Pre: None
// Post: Returns the total minutes spent delivering
int Driver::getTotalMinDelivering() {
    return Time::elapsedMin(timeDeparted, timeDelivered);
}

// Pre: None
// Post: Returns the total minutes spent driving
int Driver::getTotalMinDriving() {
    return Time::elapsedMin(timeDeparted, timeArrived);
}

// Pre: None
// Post: Returns a string containing the driver’s name, state and if the driver is delivering an order,
// the departure time and toString of the order being delivered.
string Driver::toString() {
    string stringStatement;

    if (delivering){
        stringStatement = "Name: " + name + "\nState: Is delivering.\n" + "Departure Date: " + timeDeparted.toString() + order->toString();
    } else{
        stringStatement = "Name: " + name + "\nState: ";
        if(loggedIn)
        {
            stringStatement += "Ready to take order";
        }
        else {
            stringStatement += "Not logged in.";
        }
    }

    return stringStatement;
}

#endif //FINALPROJECT_DRIVER_HPP
