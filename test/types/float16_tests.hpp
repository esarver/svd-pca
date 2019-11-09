#include "gtest/gtest.h"

#include <inttypes.h>
#include "float16.hpp"

TEST(Float16, CanConvertToFloat)
{
    float expected = 1.5f;

    f16 test = floatToF16(expected);

    EXPECT_EQ(f16ToFloat(test), expected);
}

TEST(Float16, CanConvertToDouble)
{
    double expected = 1.5;

    f16 test = floatToF16(expected);

    EXPECT_EQ(f16ToDouble(test), expected);
}

TEST(Float16, CanBeGeneratedFromFloat)
{
    float value = 1.5f;

    f16 test = floatToF16(value);

    uint16_t expected = 0x3E00;

    EXPECT_EQ((uint16_t)test, expected);
}

TEST(Float16, CanBeGeneratedFromDouble)
{
    double value = 1.5;

    f16 test = doubleToF16(value);

    uint16_t expected = 0x3E00;

    EXPECT_EQ((uint16_t)test, expected);
}
