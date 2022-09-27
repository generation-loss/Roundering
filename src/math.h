/*
Copyright (c) 2022 Generation Loss Interactive

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __ROUNDERING_MATH_H__
#define __ROUNDERING_MATH_H__

#include <math.h>


#define FIXED_INT_AS_FLOAT (0)

#if FIXED_INT_AS_FLOAT
typedef float fixedInt;
#define FIXED_INT_SCALE (1.0f)
#else
typedef int fixedInt;
#define FIXED_INT_BIT_SHIFT (15)
#define FIXED_INT_SCALE (1<<FIXED_INT_BIT_SHIFT)
#endif

static inline fixedInt toFixedInt(float val)
{
	return (fixedInt)(val * FIXED_INT_SCALE);
}

static inline float toFloat(fixedInt val)
{
	return (float)val / (float)FIXED_INT_SCALE;
}

typedef struct fixedInt2
{
	fixedInt x;
	fixedInt y;
} fixedInt2;

typedef struct fixedInt3
{
	fixedInt x;
	fixedInt y;
	fixedInt z;
} fixedInt3;

typedef struct fixedInt4
{
	fixedInt x;
	fixedInt y;
	fixedInt z;
	fixedInt w;
} fixedInt4;

typedef struct fixedInt4x4
{
    union
    {
        struct
        {
            fixedInt m00;
            fixedInt m01;
            fixedInt m02;
            fixedInt m03;
            fixedInt m10;
            fixedInt m11;
            fixedInt m12;
            fixedInt m13;
            fixedInt m20;
            fixedInt m21;
            fixedInt m22;
            fixedInt m23;
            fixedInt m30;
            fixedInt m31;
            fixedInt m32;
            fixedInt m33;
        };
        fixedInt m[16];
		fixedInt4 mm[4];
    };
} fixedInt4x4;

// fixedInt

static inline fixedInt fixedInt_add(fixedInt a, fixedInt b)
{
	return a + b;
}

static inline fixedInt fixedInt_subtract(fixedInt a, fixedInt b)
{
	return a - b;
}

static inline fixedInt fixedInt_multiply(fixedInt a, fixedInt b)
{
#if FIXED_INT_AS_FLOAT
	return a * b;
#else
	return (fixedInt)(((long long)(a) * (long long)b) / FIXED_INT_SCALE);
#endif
}

static inline fixedInt fixedInt_divide(fixedInt a, fixedInt b)
{
#if FIXED_INT_AS_FLOAT
	return a / b;
#else
	return (fixedInt)(((long long)(a) * FIXED_INT_SCALE) / (long long)b);
#endif
}

// fixedInt2

fixedInt2 fixedInt2_add(fixedInt2 a, fixedInt2 b);
fixedInt2 fixedInt2_add_scalar(fixedInt2 a, fixedInt b);
fixedInt2 fixedInt2_subtract(fixedInt2 a, fixedInt2 b);
fixedInt2 fixedInt2_subtract_scalar(fixedInt2 a, fixedInt b);
fixedInt2 fixedInt2_multiply_scalar(fixedInt2 a, fixedInt b);
fixedInt2 fixedInt2_divide_scalar(fixedInt2 a, fixedInt b);
fixedInt fixedInt2_dot(fixedInt2 a, fixedInt2 b);
fixedInt fixedInt2_length(fixedInt2 v);

// fixedInt3

fixedInt3 fixedInt3_add(fixedInt3 a, fixedInt3 b);
fixedInt3 fixedInt3_add_scalar(fixedInt3 a, fixedInt b);
fixedInt3 fixedInt3_subtract(fixedInt3 a, fixedInt3 b);
fixedInt3 fixedInt3_subtract_scalar(fixedInt3 a, fixedInt b);
fixedInt3 fixedInt3_multiply_scalar(fixedInt3 a, fixedInt b);
fixedInt3 fixedInt3_divide_scalar(fixedInt3 a, fixedInt b);
fixedInt fixedInt3_dot(fixedInt3 a, fixedInt3 b);
fixedInt fixedInt3_length(fixedInt3 v);
fixedInt3 fixedInt3_normalize(fixedInt3 unnormalized);
fixedInt3 fixedInt3_cross(fixedInt3 a, fixedInt3 b);
fixedInt2 fixedInt3_xy(fixedInt3 v);

// fixedInt4

fixedInt4 fixedInt4_add(fixedInt4 a, fixedInt4 b);
fixedInt4 fixedInt4_add_scalar(fixedInt4 a, fixedInt b);
fixedInt4 fixedInt4_subtract(fixedInt4 a, fixedInt4 b);
fixedInt4 fixedInt4_subtract_scalar(fixedInt4 a, fixedInt b);
fixedInt4 fixedInt4_multiply_scalar(fixedInt4 a, fixedInt b);
fixedInt4 fixedInt4_divide_scalar(fixedInt4 a, fixedInt b);
fixedInt fixedInt4_dot(fixedInt4 a, fixedInt4 b);
fixedInt3 fixedInt4_xyz(fixedInt4 v);

// fixedInt4x4

fixedInt4 fixedInt4x4_multiply_fixedInt4(fixedInt4x4 a, fixedInt4 b);
fixedInt4x4 fixedInt4x4_multiply_fixedInt4x4(fixedInt4x4 a, fixedInt4x4 b);

// misc

fixedInt fixedInt_min(fixedInt a, fixedInt b);
fixedInt fixedInt_max(fixedInt a, fixedInt b);
fixedInt fixedInt_clamp(fixedInt val, fixedInt minVal, fixedInt maxVal);

// misc

int int_min(int a, int b);
int int_max(int a, int b);
int int_clamp(int val, int minVal, int maxVal);

//camera

typedef struct camera
{
	fixedInt4x4 view;
	fixedInt4x4 project;
	fixedInt4x4 viewProject;
} camera;

void camera_perspective(camera *camera, const fixedInt fovy, const fixedInt aspect, const fixedInt near, const fixedInt far);
void camera_look_at(camera *camera, const fixedInt3 eye, const fixedInt3 center, const fixedInt3 up);
void camera_update_view_project(camera *camera);

#endif /* __ROUNDERING_MATH_H__ */
