#pragma once
// From https://blog.fpmurphy.com/2008/12/half-precision-floating-point-format_14.html
/*
**  This program is free software; you can redistribute it and/or modify it under
**  the terms of the GNU Lesser General Public License, as published by the Free
**  Software Foundation; either version 2 of the License, or (at your option) any
**  later version.
**
**   IEEE 758-2008 Half-precision Floating Point Format
**   --------------------------------------------------
**
**   | Field    | Last | First | Note
**   |----------|------|-------|----------
**   | Sign     | 15   | 15    |
**   | Exponent | 14   | 10    | Bias = 15
**   | Fraction | 9    | 0     |
*/

#include <stdio.h>
#include <inttypes.h>

typedef uint16_t f16;

/* ----- prototypes ------ */
float f16ToFloat(f16);
f16 floatToF16(float);
double f16ToDouble(f16);
f16 doubleToF16(double);
static uint32_t f16ToFloatI(f16);
static f16 floatToF16I(uint32_t);
