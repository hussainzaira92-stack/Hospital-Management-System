#include "validator.h"
#include"stringHelper.h"
#include <cctype>
#include<cstdio>
#include <ctime>
bool Validator::validateID(int id)
{

    return id > 0;
}
bool Validator::validateDate(
    const char* date
) {

    int day;

    int month;

    int year;

    // PARSE DATE

    if (

        sscanf_s(

            date,

            "%d-%d-%d",

            &day,

            &month,

            &year

        ) != 3
        ) {

        return false;
    }

    // BASIC RANGE CHECKS

    if (

        day < 1
        || day > 31

        ||

        month < 1
        || month > 12

        ||

        year < 2025
        ) {

        return false;
    }

    // CURRENT DATE

    time_t t = time(0);

    tm now;

    localtime_s(&now, &t);

    int currentDay =
        now.tm_mday;

    int currentMonth =
        now.tm_mon + 1;

    int currentYear =
        now.tm_year + 1900;

    // OLD YEAR

    if (year < currentYear) {

        return false;
    }

    // OLD MONTH

    if (

        year == currentYear

        &&

        month < currentMonth
        ) {

        return false;
    }

    // OLD DAY

    if (

        year == currentYear

        &&

        month == currentMonth

        &&

        day < currentDay
        ) {

        return false;
    }

    return true;
}
bool Validator::validateTimeSlot( const char* slot)
{

    const char validSlots[8][6] =  { "09:00",  "10:00","11:00", "12:00", "13:00", "14:00","15:00", "16:00" };

    for (int i = 0; i < 8; i++) 
    {

        if (StringHelper::compare(slot,validSlots[i]) == 0)
        {

            return true;
        }
    }

    return false;
}
bool Validator::validateContact( const char* contact) 
{

    if (StringHelper::length(contact) != 11)
        return false;

    for (int i = 0; i < 11; i++)
    {

        if (!isdigit(contact[i]))
            return false;
    }

    return true;
}
bool Validator::validatePassword( const char* password)
{

    return StringHelper::length(password) >= 6;
}
bool Validator::validatePositiveFloat( float value) 
{

    return value > 0;
}

bool Validator::validateMenuChoice( int choice, int min, int max)
{

    return choice >= min &&
        choice <= max;
}
bool Validator::validateAge(int age) 
{

    return age > 0 &&  age <= 120;
}

bool Validator::validateGender(char gender)
{

    return gender == 'M' ||
        gender == 'F';
}