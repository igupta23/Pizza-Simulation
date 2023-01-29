#include <iostream>
#include "Restaurant.hpp"
#include "Time.hpp"


using namespace std;

int main() {
    Restaurant res1;
    Driver dan("Dan");
    Driver adam("Adam");

    res1.addDriver(&dan);
    res1.addDriver(&adam);

    Time time1(10, 00);
    Time time2(10, 15);
    Time time3(10, 30);
    Time time4(10, 45);
    Time time5(11, 00);
    Order ord1(time1, "2 cheese to 120 West Mango Lane");

    res1.addOrder(&ord1);
    dan.login();

    res1.serveNextOrder();
    res1.departNextOrder(&dan, time2);

    Order ord2(time3, "7 goats to 140 Milner Avenue");
    res1.addOrder(&ord2);
    adam.login();

    Order ord3(time4, "12 bears to 12 Honey Badger Aquarium");
    res1.addOrder(&ord3);
    res1.serveNextOrder();

    cout << "Report 1: "<< endl;
    res1.status();

    res1.deliver(&dan, time4, 4.50);
    dan.arrive(time5);

    cout << "Report 2: "<< endl;
    Time time6(11, 30);
    Time time7(12, 00);
    res1.departNextOrder(&dan, time5);
    res1.deliver(&dan, time6, 4.75);
    dan.arrive(time7);
    res1.status();
    cout<< "Summary: " << endl;
    res1.summary();
    cout << endl;
    //cout << res1.getDriver("Dan")->toString() << endl;
    return 0;
}

