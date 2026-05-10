#include "stringHelper.h"

void StringHelper::copy( char* dest, const char* src)
 {

    int i = 0;

    while (src[i] != '\0') {

        dest[i] = src[i];

        i++;
    }

    dest[i] = '\0';
}
int StringHelper::length( const char* str)
{

    int len = 0;

    while (str[len] != '\0') {

        len++;
    }

    return len;
}
bool StringHelper::compare( const char* a, const char* b)
 {

    int i = 0;

    while ( a[i] != '\0' && b[i] != '\0')
    {

        if (a[i] != b[i]) 
        {

            return false;
        }

        i++;
    }

    return a[i] == b[i];
}