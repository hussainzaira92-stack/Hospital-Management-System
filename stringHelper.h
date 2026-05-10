#ifndef STRINGHELPER_H
#define STRINGHELPER_H

class StringHelper 
{

public:

    static void copy(char*, const char*);

    static int length(const char*);

    static bool compare(
        const char*,
        const char*
    );
};

#endif
