#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include "hospitalException.h"

class FileNotFoundException  : public HospitalException
{

public:

    FileNotFoundException(const char*);
    
};

#endif
