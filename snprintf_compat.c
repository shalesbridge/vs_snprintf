///////////////////////////////////////////////////////////////////////////////
//
// snprintf_compat.c
//
// Compatibility wrapper providing snprintf for VS2008
//
// $Revision$
// $Date$
// $Author$
// $HeadURL$
//
// Original Creation Date: 2017-05-30
// Author: Brandon Huber
//
//////////////////////////////////////////////////////////////////////////////


// When compiling under Visual Studio 2015, which introduced support for
// "snprintf", _MSC_VER == 1900.  Note that we also check to see if snprintf
// has already been defined so as not to trample another implementation of it.
//
#if defined(_MSC_VER) && _MSC_VER < 1900 && !defined(snprintf)

#include "stdarg.h" // va_list and friends


/*
 * Calculates what the size of a formatted string will be after being run
 * through sprintf().
 */
int predictFormattedStringSize(const char *format, ...)
{
    va_list vl;
    int calculated_count;
    FILE *fptr;

    fptr = fopen("NUL", "w");
    if (ftpr == NULL)
    {
        //TODO: Add error handling here.
        
        return NULL;
    }

    va_start(vl, format);
    calculated_count = vfprintf(fptr, format, vl);
    va_end(vl);
    if (calculated_count < 0)
    {
        //TODO: Add error handling here.
        
        return NULL;
    }

    if (fclose(fptr))
    {
        //TODO: Add error handling here.
        
        return NULL;
    }
    return calculated_count;

}

/* Visual Studio's _vsnprintf differs from the standard C snprintf in the
 * following ways:
 *      1) If there is not enough space in the destination string, "s",
 *
 *
 */
int snprintf(char *s, size_t n, const char *format, ...)
{
    size_t r;
    size_t count;
    int calculated_size;
    va_list vl;

    // NOTE: calculated_size does not include the terminating null character.
    va_start(vl, format);
    calculated_size = _vscprintf(format, vl);
    va_end(vl);


    va_start(vl, format);
    r = _vsnprintf(s, n, format, vl);
    va_end(vl);

    if (r < 0)
    {
        s[n - 1] = '\0';
    }
    return calculated_size;
}


#define snprintf _snprintf
