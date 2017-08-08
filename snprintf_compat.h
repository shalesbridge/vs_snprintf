#ifdef __cplusplus
extern "C"
{
#endif

///////////////////////////////////////////////////////////////////////////////
//
// snprintf_compat.h
//
// Compatibility library for providing snprintf to VS 2008.
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

// Microsoft's _snprintf is not strictly compatible with snprintf, so we have
// to do things the hard way instead of just doing:
// #define snprintf _snprintf

int snprintf ( char * s, size_t n, const char * format, ... );

#else

// If snprintf already exists, it should be in "stdio.h".
#include "stdio.h"

#endif


#ifdef __cplusplus
}
#endif
