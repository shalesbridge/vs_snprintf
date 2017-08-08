///////////////////////////////////////////////////////////////////////////////
//
// tests.c
//
// Google tests for snprintf_compat.
//
// Original Creation Date: 2017-06-04
// Author: Brandon Huber
//
//////////////////////////////////////////////////////////////////////////////

#include "gtest/gtest.h"
#include "snprintf_compat.h"

// Tests putting a single string into sprintf with insufficient space in the
// destination.
TEST(SnprintfTest, SingleStringWithInsufficientSpace)
{
    int r;
    char dest[] = "ZZZZZZZZZZZZZZZ";
    r = snprintf(dest, 3, "%s", "foo");
    EXPECT_STREQ("fo", dest);
    EXPECT_EQ(3, r);
    //
    // Make sure that snprintf() did not alter anything past where it needed to
    // (being, the position of the null terminator).
    EXPECT_EQ('Z', dest[strlen(dest) + 1]);
    // EXPECT_EQ('Z', dest[3]);
    // EXPECT_STREQ("fooZZZZZZZZZZZZ", dest);
}

// Tests putting a single string into sprintf with more than enough space in the
// destination.
TEST(SnprintfTest, SingleStringWithMoreThanEnoughSpace)
{
    int r;
    char dest[] = "ZZZZZZZZZZZZZZZ";
    r = snprintf(dest, strlen(dest) - 1, "%s", "foo");
    EXPECT_EQ(3, r);
    //
    // Make sure that snprintf() did not alter anything past where it needed to
    // (being, the position of the null terminator).
    EXPECT_EQ('Z', dest[strlen(dest) + 1]);
    EXPECT_STREQ("foo", dest);
}
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
