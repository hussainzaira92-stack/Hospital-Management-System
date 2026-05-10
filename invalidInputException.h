#ifndef INVALIDINPUTEXCEPTION_H
#define INVALIDINPUTEXCEPTION_H

#include "hospitalException.h"

class InvalidInputException : public HospitalException
{

public:

    InvalidInputException(const char*);
    
};

#endif
