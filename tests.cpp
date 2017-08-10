///////////////////////////////////////////////////////////////////////////////
//
// tests.cpp
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
// destination, which is 1 byte too short.
TEST(SnprintfTest, SingleStringWithInsufficientSpace1)
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
}

// Tests putting a single string into sprintf with insufficient space in the
// destination, which is 2 bytes too short.
TEST(SnprintfTest, SingleStringWithInsufficientSpace2)
{
    int r;
    char dest[] = "ZZZZZZZZZZZZZZZ";
    r = snprintf(dest, 2, "%s", "foo");
    EXPECT_STREQ("f", dest);
    EXPECT_EQ(3, r);
    //
    // Make sure that snprintf() did not alter anything past where it needed to
    // (being, the position of the null terminator).
    EXPECT_EQ('Z', dest[strlen(dest) + 1]);
}

// Tests putting a single string into sprintf with insufficient space in the
// destination, which is 3 bytes too short.
TEST(SnprintfTest, SingleStringWithInsufficientSpace3)
{
    int r;
    char dest[] = "ZZZZZZZZZZZZZZZ";
    r = snprintf(dest, 1, "%s", "foo");
    EXPECT_STREQ("", dest);
    EXPECT_EQ(3, r);
    //
    // Make sure that snprintf() did not alter anything past where it needed to
    // (being, the position of the null terminator).
    EXPECT_EQ('Z', dest[strlen(dest) + 1]);
}

// Tests putting a single string into sprintf with only one char of space
// available.
TEST(SnprintfTest, SingleStringWithSingleCharOfSpace)
{
    int r;
    char dest[] = "ZZZZZZZZZZZZZZZ";
    r = snprintf(dest, 1, "%s", "foo");
    EXPECT_STREQ("", dest);
    EXPECT_EQ(3, r);
    //
    // Make sure that snprintf() did not alter anything past where it needed to
    // (being, the position of the null terminator).
    EXPECT_EQ('Z', dest[strlen(dest) + 1]);
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

// Tests putting a single string into sprintf while providing "0" to snprintf as
// the count of available bytes in the destination.
TEST(SnprintfTest, SingleStringWithZeroCount)
{
    int r;
    char dest[] = "ZZZZZZZZZZZZZZZ";
    r = snprintf(dest, 0, "%s", "foo");
    EXPECT_STREQ("ZZZZZZZZZZZZZZZ", dest);
    EXPECT_EQ(3, r);
    //
    // Make sure that snprintf() did not alter anything past where it needed to
    // (being, the position of the null terminator).
//    EXPECT_EQ('Z', dest[strlen(dest) + 1]);
}

// Tests putting two strings into sprintf with more than enough space in the
// destination.
TEST(SnprintfTest, TwoStringsWithMoreThanEnoughSpace)
{
    int r;
    char dest[] = "ZZZZZZZZZZZZZZZ";
    r = snprintf(dest, strlen(dest) - 1, "%s%s", "foo", "bar");
    EXPECT_EQ(6, r);
    //
    // Make sure that snprintf() did not alter anything past where it needed to
    // (being, the position of the null terminator).
    EXPECT_EQ('Z', dest[strlen(dest) + 1]);
    EXPECT_STREQ("foobar", dest);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
