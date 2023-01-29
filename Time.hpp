//
// Created by Ishika Gupta on 12/7/21.
//

#ifndef FINALPROJECT_TIME_HPP
#define FINALPROJECT_TIME_HPP

#include <iostream>
#include <string>

using namespace std;


// The Time class represents a time of day in 24-hour time with hours and minutes.
class Time {

private:

    int hours;
    int minutes;

public:
    Time();
    Time(int h, int m);
    static int elapsedMin(Time t1, Time t2);
    string toString();

};


// Pre: None
// Post: Creates a time with default values for data members.
Time::Time() : hours(0), minutes(0) {}

// Pre: A valid time with 0 <= h < 24 and 0 <= m < 60.
// Post: Constructor that creates an object Time, with the given h hour and m min.
Time::Time(int h, int m)
{
    if(h >= 0 && h < 24 && m >= 0 && m < 60)
    {
        hours = h;
        minutes = m;
    }
    else
    {
        throw(logic_error("Invalid time."));
    }
}

// Pre: None
// Post: Returns the difference in minutes between t1 and t2. Assumes t2 is between 00:00 and 23:59 hours after t1.
int Time::elapsedMin(Time t1, Time t2)
{
    int sum = 0;

    int hourDifference = t1.hours - t2.hours;

    if(hourDifference > 0)
    {
        hourDifference -= 24;
    }

    hourDifference *= (-1);

    sum += (hourDifference * 60);

    int minutesDifference = t2.minutes - t1.minutes;

    sum += minutesDifference;

    return sum;
}

// Pre: None
// Post: Converts an object Time to a string containing the hour and minute
string Time::toString()
{
    string t = "";

    if(hours < 10)
    {
        t += "0";
    }

    t += to_string(hours) + ":";

    if(minutes < 10)
    {
        t += "0";
    }

    t += to_string(minutes);

    return t;
}

#endif //FINALPROJECT_TIME_HPP
