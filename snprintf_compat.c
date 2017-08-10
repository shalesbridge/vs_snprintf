///////////////////////////////////////////////////////////////////////////////
//
// snprintf_compat.c
//
// Compatibility wrapper providing snprintf for VS2008
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

#include "stdio.h"
#include "stdarg.h" // va_list and friends
#include "crtdefs.h" // size_t
#include "snprintf_compat.h"




int snprintf(char *s, size_t n, const char *format, ...)
{
    size_t r;
    int calculated_size;
    va_list vl;

    // NOTE: calculated_size does not include the terminating null character.
    va_start(vl, format);
    calculated_size = _vscprintf(format, vl);
    va_end(vl);

    va_start(vl, format);
    r = _vsnprintf(s, n, format, vl);
    va_end(vl);

    // Null-terminate the string if there was insufficient space.
    // This brings it in line with the standard snprintf's behavior.
    //
    // NOTE: Contrary to the documentation for VS2008's _vsnprintf at
    // https://msdn.microsoft.com/en-us/library/1kt27hek(v=vs.90).aspx :
    // _vsnprintf does NOT appear to return a negative value if truncation
    // occurs due to "n" not being large enough to accomadate the full string.
    // Rather, it returns the number of bytes that would be written if "n" were
    // large enough (happily, this is also how the standard snprintf function
    // behaves).
    if (r >= n)
    {
        if (n > 0) s[n - 1] = '\0';
    }

    // The standard snprintf function returns a negative number if an encoding
    // error occurred.  The documentation for VS2008's _vsnprintf (
    // https://msdn.microsoft.com/en-us/library/1kt27hek(v=vs.90).aspx ) does
    // not specify what happens if an encoding error occurs, and incorrectly
    // specifies what a negative return value from _vsnprintf means.  So,
    // there's no guarantee that a negative return value from from _vsnprintf
    // means the same thing as for the standard snprintf, but its our best
    // guess.
    if (r < 0) return r;

    return calculated_size;
}


#endif
