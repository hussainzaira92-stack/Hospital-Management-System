#ifndef INSUFFICIENTFUNDSEXCEPTION_H
#define INSUFFICIENTFUNDSEXCEPTION_H

#include "hospitalException.h"
class InsufficientFundsException : public HospitalException 
{

public:

    InsufficientFundsException(const char*);
    
};

#endif
