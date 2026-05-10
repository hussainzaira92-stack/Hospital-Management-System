#ifndef SLOTUNAVAILABLEEXCEPTION_H
#define SLOTUNAVAILABLEEXCEPTION_H

#include "hospitalException.h"
class SlotUnavailableException  : public HospitalException 
{

public:

    SlotUnavailableException(  const char* );
};

#endif
