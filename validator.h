#ifndef VALIDATOR_H
#define VALIDATOR_H

class Validator
{

public:

    static bool validateID(int);
    static bool validateDate(const char*);
    static bool validateTimeSlot(const char*);
    static bool validateContact(const char*);
    static bool validatePassword(const char*);
    static bool validatePositiveFloat(float);
    static bool validateMenuChoice( int choice,   int min, int max );
    static bool validateAge(int);
    static bool validateGender(char);
};

#endif
