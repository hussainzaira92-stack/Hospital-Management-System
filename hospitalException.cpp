#include "hospitalException.h"
#include"stringHelper.h"


HospitalException::HospitalException(  const char* msg) 
{

    StringHelper::copy(message, msg);
}

const char* HospitalException::what() const 
{

    return message;
}

HospitalException::~HospitalException() {}