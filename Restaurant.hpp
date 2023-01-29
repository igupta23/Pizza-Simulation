//
// Created by Ishika Gupta on 12/7/21.
//

#ifndef FINALPROJECT_RESTAURANT_HPP
#define FINALPROJECT_RESTAURANT_HPP

#include <queue>
#include <list>
#include <string>
#include "Driver.hpp"

using namespace std;

// The Restaurant class keeps track of all drivers and orders in the system,
// including logged-out drivers and completed orders.
class Restaurant {

private:

    queue<Order*> orders;
    queue<Order*> completedOrders;
    list<Driver*> Drivers;
    int totalOrdersCompleted;
    int totalTime;
    int totalDrivers;

public:
    Restaurant();
    void status();
    void summary();
    void addDriver(Driver* driver);
    Driver* getDriver(string name);
    void addOrder(Order* order);
    void serveNextOrder();
    void departNextOrder(Driver* driver, Time time);
    void deliver(Driver* driver, Time time, float tip);

};

// Pre: None
// Post: Creates a restaurant in an initial state, with no drivers or orders.
Restaurant::Restaurant()
        : totalOrdersCompleted(0), totalTime(0), totalDrivers(0) {}

// Pre: None
// Post: Prints status of orders and logged-in drivers, as specified by the “status” command description.
void Restaurant::status()
{
    cout << "Orders waiting to be cooked:" << endl;
    queue<Order*> copyQ = orders;
    while(!copyQ.empty())
    {
        cout << copyQ.front()->toString() << endl;
        copyQ.pop();
    }

    cout << "Orders waiting to depart:" << endl;
    queue<Order*> copyQ2 = completedOrders;
    while(!copyQ2.empty())
    {
        cout << copyQ2.front()->toString() << endl;
        copyQ2.pop();
    }

    cout << "Drivers:" << endl;
    for(Driver* driver : Drivers)
    {
        cout << driver->toString() << endl;
    }
    cout << endl;
}

// Pre: None
// Post: Prints summary statistics on orders and drivers, as specified by the “summary” command description.
void Restaurant::summary()
{
    cout << "Number of orders completed: " << totalOrdersCompleted << endl;
    cout << "Average time per order: " << totalTime / totalOrdersCompleted << endl;
    for(Driver* driver : Drivers)
    {
        cout << "Driver " << driver->getName() << ":" << endl;
        cout << "Number of deliveries completed: " << driver->getTotalDeliveries() << endl;
        if(driver->getTotalDeliveries() != 0)
        {
            cout << "Average time per delivery: "
                 << ((driver->getTotalMinDelivering()) / (driver->getTotalDeliveries())) << endl;
        }
        else
        {
            cout << "Average time per delivery: 0" << endl;
        }
        cout << "Total driving time: " << driver->getTotalMinDriving() << endl;
        cout << "Total tips: " << driver->getTotalTips() << endl;
    }
}



// Pre: None
// Post: Adds the given driver to the system
void Restaurant::addDriver(Driver* driver)
{
    Drivers.push_back(driver);
    totalDrivers++;
}

// Pre: None
// Post: If a driver with the given name exists within the system (logged in or not),
// returns a pointer to that driver. Otherwise, returns a null pointer.
Driver* Restaurant::getDriver(string name)
{
    for(Driver* driver : Drivers)
    {
        if(driver->getName() == name)
        {
            return driver;
        }
    }

    throw(logic_error("Driver does not work here."));
}

// Pre: None
// Post: Adds the given order to the system, enqueuing it for cooking.
void Restaurant::addOrder(Order* order)
{
    orders.push(order);
}

// Pre: The cooking queue is not empty.
// Post: Removes the oldest order from the cooking queue and enqueues it for departure.
void Restaurant::serveNextOrder()
{
    if(!orders.empty())
    {
        completedOrders.push(orders.front());
        completedOrders.front()->depart();
        orders.pop();
    }
    else
    {
        throw(logic_error("There are no orders."));
    }
}

// Pre: The departure queue is not empty.
// Post: Removes the oldest order from the departure queue and returns it.
void Restaurant::departNextOrder(Driver* driver, Time time)
{
    if(!completedOrders.empty())
    {
        driver->depart(time, completedOrders.front());
        completedOrders.pop();
    }
    else
    {
        throw(logic_error("There are no orders to be delivered."));
    }
}

// Pre: None
// Post: The order carried by the driver is delivered at the given time. The driver receives the given tip.
void Restaurant::deliver(Driver* driver, Time time, float tip)
{
    totalOrdersCompleted++;
    driver->deliver(time, tip);
    completedOrders.front()->deliver(time);
    totalTime += completedOrders.front()->getMinToDelivery();
}

#endif //FINALPROJECT_RESTAURANT_HPP
