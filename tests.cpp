///////////////////////////////////////////////////////////////////////////////
//
// tests.c
//
// Google tests for snprintf_compat.
//
// $Revision$
// $Date$
// $Author$
// $HeadURL$
//
// Original Creation Date: 2017-06-04
// Author: Brandon Huber
//
//////////////////////////////////////////////////////////////////////////////

#include "gtest/gtest.h"
#include "../snprintf_compat.h"

// Tests putting a single string into sprintf with insufficient space in the
// destination.
TEST(SnprintfTest, SingleStringWithInsufficientSpace)
{
    int r;
    char dest[] = "ZZZZZZZZZZZZZZZ";
    r = snprintf(dest, 3, "%s", "foo");
    EXPECT_STREQ("fo", snprintf());
    EXPECT_EQ(3, r);
    //
    // Make sure that snprintf() did not alter anything past where it needed to
    // (being, the position of the null terminator).
    EXPECT_EQ('Z', dest[3])
}

// Tests putting a single string into sprintf with more than enough space in the
// destination.
TEST(SnprintfTest, SingleStringWithMoreThanEnoughSpace)
{
    int r;
    char dest[] = "ZZZZZZZZZZZZZZZ";
    r = snprintf(dest, strlen(dest) - 1, "%s", "foo");
    EXPECT_STREQ("foo", snprintf());
    EXPECT_EQ(strlen("foo") + 1, r);
    //
    // Make sure that snprintf() did not alter anything past where it needed to
    // (being, the position of the null terminator).
    EXPECT_EQ('Z', dest[strlen(dest) + 1])
}
