//
//  math.c
//  roundering
//
//  Created by Russell Warneboldt on 2022-09-06.
//

#include "math.h"

#pragma mark float2

float2 float2_add(float2 a, float2 b)
{
	float2 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}

float2 float2_add_scalar(float2 a, float b)
{
	float2 result;
	result.x = a.x + b;
	result.y = a.y + b;
	return result;
}

float2 float2_subtract(float2 a, float2 b)
{
	float2 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

float2 float2_subtract_scalar(float2 a, float b)
{
	float2 result;
	result.x = a.x - b;
	result.y = a.y - b;
	return result;
}

float2 float2_multiply_scalar(float2 a, float b)
{
	float2 result;
	result.x = a.x * b;
	result.y = a.y * b;
	return result;
}

float2 float2_divide_scalar(float2 a, float b)
{
	float2 result;
	result.x = a.x / b;
	result.y = a.y / b;
	return result;
}

float float2_dot(float2 a, float2 b)
{
	return (a.x * b.x) + (a.y * b.y);
}

float float2_length(float2 v)
{
	return sqrtf(float2_dot(v, v));
}

#pragma mark float3

float3 float3_add(float3 a, float3 b)
{
	float3 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return result;
}

float3 float3_add_scalar(float3 a, float b)
{
	float3 result;
	result.x = a.x + b;
	result.y = a.y + b;
	result.z = a.z + b;
	return result;
}

float3 float3_subtract(float3 a, float3 b)
{
	float3 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

float3 float3_subtract_scalar(float3 a, float b)
{
	float3 result;
	result.x = a.x - b;
	result.y = a.y - b;
	result.z = a.z - b;
	return result;
}

float3 float3_multiply_scalar(float3 a, float b)
{
	float3 result;
	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return result;
}

float3 float3_divide_scalar(float3 a, float b)
{
	float3 result;
	result.x = a.x / b;
	result.y = a.y / b;
	result.z = a.z / b;
	return result;
}

float float3_dot(float3 a, float3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

float float3_length(float3 v)
{
	return sqrtf(float3_dot(v, v));
}

float3 float3_normalize(float3 unnormalized)
{
	float length = float3_length(unnormalized);
	return float3_divide_scalar(unnormalized, length);
}

float3 float3_cross(float3 a, float3 b)
{
	float3 cross;
	cross.x = (a.y * b.z) - (a.z * b.y);
	cross.y = (a.z * b.x) - (a.x * b.z);
	cross.z = (a.x * b.y) - (a.y * b.x);
	return cross;
}

float2 float3_xy(float3 v)
{
	float2 result;
	result.x = v.x;
	result.y = v.y;
	return result;
}

#pragma mark float4

float4 float4_add(float4 a, float4 b)
{
	float4 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return result;
}

float4 float4_add_scalar(float4 a, float b)
{
	float4 result;
	result.x = a.x + b;
	result.y = a.y + b;
	result.z = a.z + b;
	result.w = a.w + b;
	return result;
}

float4 float4_subtract(float4 a, float4 b)
{
	float4 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return result;
}

float4 float4_subtract_scalar(float4 a, float b)
{
	float4 result;
	result.x = a.x - b;
	result.y = a.y - b;
	result.z = a.z - b;
	result.w = a.w - b;
	return result;
}

float4 float4_multiply_scalar(float4 a, float b)
{
	float4 result;
	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	result.w = a.w * b;
	return result;
}

float4 float4_divide_scalar(float4 a, float b)
{
	float4 result;
	result.x = a.x / b;
	result.y = a.y / b;
	result.z = a.z / b;
	result.w = a.w / b;
	return result;
}

float float4_dot(float4 a, float4 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

float3 float4_xyz(float4 v)
{
	float3 result;
	result.x = v.x;
	result.y = v.y;
	result.z = v.z;
	return result;
}

#pragma mark float4x4

float4 float4x4_multiply_float4(float4x4 a, float4 b)
{
	float4 result;
	result.x = (a.m00 * b.x) + (a.m10 * b.y) + (a.m20 * b.z) + (a.m30 * b.w);
	result.y = (a.m01 * b.x) + (a.m11 * b.y) + (a.m21 * b.z) + (a.m31 * b.w);
	result.z = (a.m02 * b.x) + (a.m12 * b.y) + (a.m22 * b.z) + (a.m32 * b.w);
	result.w = (a.m03 * b.x) + (a.m13 * b.y) + (a.m23 * b.z) + (a.m33 * b.w);
	return result;
}

float4x4 float4x4_multiply_float4x4(float4x4 a, float4x4 b)
{
	float4x4 result;
	
	result.m00 = (a.m00 * b.m00) + (a.m10 * b.m01) + (a.m20 * b.m02) + (a.m30 * b.m03);
	result.m01 = (a.m01 * b.m00) + (a.m11 * b.m01) + (a.m21 * b.m02) + (a.m31 * b.m03);
	result.m02 = (a.m02 * b.m00) + (a.m12 * b.m01) + (a.m22 * b.m02) + (a.m32 * b.m03);
	result.m03 = (a.m03 * b.m00) + (a.m13 * b.m01) + (a.m23 * b.m02) + (a.m33 * b.m03);
	
	result.m10 = (a.m00 * b.m10) + (a.m10 * b.m11) + (a.m20 * b.m12) + (a.m30 * b.m13);
	result.m11 = (a.m01 * b.m10) + (a.m11 * b.m11) + (a.m21 * b.m12) + (a.m31 * b.m13);
	result.m12 = (a.m02 * b.m10) + (a.m12 * b.m11) + (a.m22 * b.m12) + (a.m32 * b.m13);
	result.m13 = (a.m03 * b.m10) + (a.m13 * b.m11) + (a.m23 * b.m12) + (a.m33 * b.m13);
	
	result.m20 = (a.m00 * b.m20) + (a.m10 * b.m21) + (a.m20 * b.m22) + (a.m30 * b.m23);
	result.m21 = (a.m01 * b.m20) + (a.m11 * b.m21) + (a.m21 * b.m22) + (a.m31 * b.m23);
	result.m22 = (a.m02 * b.m20) + (a.m12 * b.m21) + (a.m22 * b.m22) + (a.m32 * b.m23);
	result.m23 = (a.m03 * b.m20) + (a.m13 * b.m21) + (a.m23 * b.m22) + (a.m33 * b.m23);
	
	result.m30 = (a.m00 * b.m30) + (a.m10 * b.m31) + (a.m20 * b.m32) + (a.m30 * b.m33);
	result.m31 = (a.m01 * b.m30) + (a.m11 * b.m31) + (a.m21 * b.m32) + (a.m31 * b.m33);
	result.m32 = (a.m02 * b.m30) + (a.m12 * b.m31) + (a.m22 * b.m32) + (a.m32 * b.m33);
	result.m33 = (a.m03 * b.m30) + (a.m13 * b.m31) + (a.m23 * b.m32) + (a.m33 * b.m33);
	
	return result;
}

#pragma mark float misc

float float_min(float a, float b)
{
	return a < b ? a : b;
}

float float_max(float a, float b)
{
	return a > b ? a : b;
}

float float_clamp(float val, float minVal, float maxVal)
{
	return float_min(maxVal, float_max(minVal, val));
}

// fixedInt2

fixedInt2 fixedInt2_add(fixedInt2 a, fixedInt2 b)
{
	fixedInt2 result;
	result.x = fixedInt_add(a.x, b.x);
	result.y = fixedInt_add(a.y, b.y);
	return result;
}

fixedInt2 fixedInt2_add_scalar(fixedInt2 a, fixedInt b)
{
	fixedInt2 result;
	result.x = fixedInt_add(a.x, b);
	result.y = fixedInt_add(a.y, b);
	return result;
}

fixedInt2 fixedInt2_subtract(fixedInt2 a, fixedInt2 b)
{
	fixedInt2 result;
	result.x = fixedInt_subtract(a.x, b.x);
	result.y = fixedInt_subtract(a.y, b.y);
	return result;
}

fixedInt2 fixedInt2_subtract_scalar(fixedInt2 a, fixedInt b)
{
	fixedInt2 result;
	result.x = fixedInt_subtract(a.x, b);
	result.y = fixedInt_subtract(a.y, b);
	return result;
}

fixedInt2 fixedInt2_multiply_scalar(fixedInt2 a, fixedInt b)
{
	fixedInt2 result;
	result.x = fixedInt_multiply(a.x, b);
	result.y = fixedInt_multiply(a.y, b);
	return result;
}

fixedInt2 fixedInt2_divide_scalar(fixedInt2 a, fixedInt b)
{
	fixedInt2 result;
	result.x = fixedInt_divide(a.x, b);
	result.y = fixedInt_divide(a.y, b);
	return result;
}

fixedInt fixedInt2_dot(fixedInt2 a, fixedInt2 b)
{
	return fixedInt_add(fixedInt_multiply(a.x, b.x), fixedInt_multiply(a.y, b.y));
}

fixedInt fixedInt2_length(fixedInt2 v)
{
	return (fixedInt)((sqrtf((float)fixedInt2_dot(v, v) / FIXED_INT_SCALE)) * FIXED_INT_SCALE);
}

// fixedInt3

fixedInt3 fixedInt3_add(fixedInt3 a, fixedInt3 b)
{
	fixedInt3 result;
	result.x = fixedInt_add(a.x, b.x);
	result.y = fixedInt_add(a.y, b.y);
	result.z = fixedInt_add(a.z, b.z);
	return result;
}

fixedInt3 fixedInt3_add_scalar(fixedInt3 a, fixedInt b)
{
	fixedInt3 result;
	result.x = fixedInt_add(a.x, b);
	result.y = fixedInt_add(a.y, b);
	result.z = fixedInt_add(a.z, b);
	return result;
}

fixedInt3 fixedInt3_subtract(fixedInt3 a, fixedInt3 b)
{
	fixedInt3 result;
	result.x = fixedInt_subtract(a.x, b.x);
	result.y = fixedInt_subtract(a.y, b.y);
	result.z = fixedInt_subtract(a.z, b.z);
	return result;
}

fixedInt3 fixedInt3_subtract_scalar(fixedInt3 a, fixedInt b)
{
	fixedInt3 result;
	result.x = fixedInt_subtract(a.x, b);
	result.y = fixedInt_subtract(a.y, b);
	result.z = fixedInt_subtract(a.z, b);
	return result;
}

fixedInt3 fixedInt3_multiply_scalar(fixedInt3 a, fixedInt b)
{
	fixedInt3 result;
	result.x = fixedInt_multiply(a.x, b);
	result.y = fixedInt_multiply(a.y, b);
	result.z = fixedInt_multiply(a.z, b);
	return result;
}

fixedInt3 fixedInt3_divide_scalar(fixedInt3 a, fixedInt b)
{
	fixedInt3 result;
	result.x = fixedInt_divide(a.x, b);
	result.y = fixedInt_divide(a.y, b);
	result.z = fixedInt_divide(a.z, b);
	return result;
}

fixedInt fixedInt3_dot(fixedInt3 a, fixedInt3 b)
{
	return fixedInt_add(fixedInt_multiply(a.x, b.x), fixedInt_add(fixedInt_multiply(a.y, b.y), fixedInt_multiply(a.z, b.z)));
}

fixedInt fixedInt3_length(fixedInt3 v)
{
	return (fixedInt)((sqrtf((float)fixedInt3_dot(v, v) / FIXED_INT_SCALE)) * FIXED_INT_SCALE);
}

fixedInt3 fixedInt3_normalize(fixedInt3 unnormalized)
{
	fixedInt length = fixedInt3_length(unnormalized);
	return fixedInt3_divide_scalar(unnormalized, length);
}

fixedInt3 fixedInt3_cross(fixedInt3 a, fixedInt3 b)
{
	fixedInt3 cross;
	cross.x = fixedInt_subtract(fixedInt_multiply(a.y, b.z), fixedInt_multiply(a.z, b.y));
	cross.y = fixedInt_subtract(fixedInt_multiply(a.z, b.x), fixedInt_multiply(a.x, b.z));
	cross.z = fixedInt_subtract(fixedInt_multiply(a.x, b.y), fixedInt_multiply(a.y, b.x));
	return cross;
}

fixedInt2 fixedInt3_xy(fixedInt3 v)
{
	fixedInt2 result;
	result.x = v.x;
	result.y = v.y;
	return result;
}

// fixedInt4

fixedInt4 fixedInt4_add(fixedInt4 a, fixedInt4 b)
{
	fixedInt4 result;
	result.x = fixedInt_add(a.x, b.x);
	result.y = fixedInt_add(a.y, b.y);
	result.z = fixedInt_add(a.z, b.z);
	result.w = fixedInt_add(a.w, b.w);
	return result;
}

fixedInt4 fixedInt4_add_scalar(fixedInt4 a, fixedInt b)
{
	fixedInt4 result;
	result.x = fixedInt_add(a.x, b);
	result.y = fixedInt_add(a.y, b);
	result.z = fixedInt_add(a.z, b);
	result.w = fixedInt_add(a.w, b);
	return result;
}

fixedInt4 fixedInt4_subtract(fixedInt4 a, fixedInt4 b)
{
	fixedInt4 result;
	result.x = fixedInt_subtract(a.x, b.x);
	result.y = fixedInt_subtract(a.y, b.y);
	result.z = fixedInt_subtract(a.z, b.z);
	result.w = fixedInt_subtract(a.w, b.w);
	return result;
}

fixedInt4 fixedInt4_subtract_scalar(fixedInt4 a, fixedInt b)
{
	fixedInt4 result;
	result.x = fixedInt_subtract(a.x, b);
	result.y = fixedInt_subtract(a.y, b);
	result.z = fixedInt_subtract(a.z, b);
	result.w = fixedInt_subtract(a.w, b);
	return result;
}

fixedInt4 fixedInt4_multiply_scalar(fixedInt4 a, fixedInt b)
{
	fixedInt4 result;
	result.x = fixedInt_multiply(a.x, b);
	result.y = fixedInt_multiply(a.y, b);
	result.z = fixedInt_multiply(a.z, b);
	result.w = fixedInt_multiply(a.w, b);
	return result;
}

fixedInt4 fixedInt4_divide_scalar(fixedInt4 a, fixedInt b)
{
	fixedInt4 result;
	result.x = fixedInt_divide(a.x, b);
	result.y = fixedInt_divide(a.y, b);
	result.z = fixedInt_divide(a.z, b);
	result.w = fixedInt_divide(a.w, b);
	return result;
}

fixedInt fixedInt4_dot(fixedInt4 a, fixedInt4 b)
{
	return fixedInt_add(fixedInt_add(fixedInt_multiply(a.x, b.x), fixedInt_multiply(a.y, b.y)), fixedInt_add(fixedInt_multiply(a.z, b.z), fixedInt_multiply(a.w, b.w)));
}

fixedInt3 fixedInt4_xyz(fixedInt4 v)
{
	fixedInt3 result;
	result.x = v.x;
	result.y = v.y;
	result.z = v.z;
	return result;
}

// fixedInt4x4

fixedInt4 fixedInt4x4_multiply_fixedInt4(fixedInt4x4 a, fixedInt4 b)
{
	fixedInt4 result;
	result.x = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m00, b.x), fixedInt_multiply(a.m10, b.y)), fixedInt_add(fixedInt_multiply(a.m20, b.z), fixedInt_multiply(a.m30, b.w)));
	result.y = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m01, b.x), fixedInt_multiply(a.m11, b.y)), fixedInt_add(fixedInt_multiply(a.m21, b.z), fixedInt_multiply(a.m31, b.w)));
	result.z = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m02, b.x), fixedInt_multiply(a.m12, b.y)), fixedInt_add(fixedInt_multiply(a.m22, b.z), fixedInt_multiply(a.m32, b.w)));
	result.w = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m03, b.x), fixedInt_multiply(a.m13, b.y)), fixedInt_add(fixedInt_multiply(a.m23, b.z), fixedInt_multiply(a.m33, b.w)));
	return result;
}

fixedInt4x4 fixedInt4x4_multiply_fixedInt4x4(fixedInt4x4 a, fixedInt4x4 b)
{
	fixedInt4x4 result;
	
	result.m00 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m00, b.m00), fixedInt_multiply(a.m10, b.m01)), fixedInt_add(fixedInt_multiply(a.m20, b.m02), fixedInt_multiply(a.m30, b.m03)));
	result.m01 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m01, b.m00), fixedInt_multiply(a.m11, b.m01)), fixedInt_add(fixedInt_multiply(a.m21, b.m02), fixedInt_multiply(a.m31, b.m03)));
	result.m02 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m02, b.m00), fixedInt_multiply(a.m12, b.m01)), fixedInt_add(fixedInt_multiply(a.m22, b.m02), fixedInt_multiply(a.m32, b.m03)));
	result.m03 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m03, b.m00), fixedInt_multiply(a.m13, b.m01)), fixedInt_add(fixedInt_multiply(a.m23, b.m02), fixedInt_multiply(a.m33, b.m03)));
	
	result.m10 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m00, b.m10), fixedInt_multiply(a.m10, b.m11)), fixedInt_add(fixedInt_multiply(a.m20, b.m12), fixedInt_multiply(a.m30, b.m13)));
	result.m11 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m01, b.m10), fixedInt_multiply(a.m11, b.m11)), fixedInt_add(fixedInt_multiply(a.m21, b.m12), fixedInt_multiply(a.m31, b.m13)));
	result.m12 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m02, b.m10), fixedInt_multiply(a.m12, b.m11)), fixedInt_add(fixedInt_multiply(a.m22, b.m12), fixedInt_multiply(a.m32, b.m13)));
	result.m13 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m03, b.m10), fixedInt_multiply(a.m13, b.m11)), fixedInt_add(fixedInt_multiply(a.m23, b.m12), fixedInt_multiply(a.m33, b.m13)));
	
	result.m20 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m00, b.m20), fixedInt_multiply(a.m10, b.m21)), fixedInt_add(fixedInt_multiply(a.m20, b.m22), fixedInt_multiply(a.m30, b.m23)));
	result.m21 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m01, b.m20), fixedInt_multiply(a.m11, b.m21)), fixedInt_add(fixedInt_multiply(a.m21, b.m22), fixedInt_multiply(a.m31, b.m23)));
	result.m22 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m02, b.m20), fixedInt_multiply(a.m12, b.m21)), fixedInt_add(fixedInt_multiply(a.m22, b.m22), fixedInt_multiply(a.m32, b.m23)));
	result.m23 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m03, b.m20), fixedInt_multiply(a.m13, b.m21)), fixedInt_add(fixedInt_multiply(a.m23, b.m22), fixedInt_multiply(a.m33, b.m23)));
	
	result.m30 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m00, b.m30), fixedInt_multiply(a.m10, b.m31)), fixedInt_add(fixedInt_multiply(a.m20, b.m32), fixedInt_multiply(a.m30, b.m33)));
	result.m31 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m01, b.m30), fixedInt_multiply(a.m11, b.m31)), fixedInt_add(fixedInt_multiply(a.m21, b.m32), fixedInt_multiply(a.m31, b.m33)));
	result.m32 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m02, b.m30), fixedInt_multiply(a.m12, b.m31)), fixedInt_add(fixedInt_multiply(a.m22, b.m32), fixedInt_multiply(a.m32, b.m33)));
	result.m33 = fixedInt_add(fixedInt_add(fixedInt_multiply(a.m03, b.m30), fixedInt_multiply(a.m13, b.m31)), fixedInt_add(fixedInt_multiply(a.m23, b.m32), fixedInt_multiply(a.m33, b.m33)));
	
	return result;
}

// misc

fixedInt fixedInt_min(fixedInt a, fixedInt b)
{
	return a < b ? a : b;
}

fixedInt fixedInt_max(fixedInt a, fixedInt b)
{
	return a > b ? a : b;
}

fixedInt fixedInt_clamp(fixedInt val, fixedInt minVal, fixedInt maxVal)
{
	return fixedInt_min(maxVal, fixedInt_max(minVal, val));
}

// misc

int int_min(int a, int b)
{
	return a < b ? a : b;
}

int int_max(int a, int b)
{
	return a > b ? a : b;
}

int int_clamp(int val, int minVal, int maxVal)
{
	return int_min(maxVal, int_max(minVal, val));
}

// fixedCamera

void fixedCamera_perspective(fixedCamera *camera, const fixedInt fovy, const fixedInt aspect, const fixedInt near, const fixedInt far)
{
	fixedInt angle  = fixedInt_multiply(fixedInt_multiply(toFixedInt(0.5f), fovy), toFixedInt(3.14159265358979323846264338327950288f / 180.0f)); // radians
	
	float numerator = toFixedInt(1.0f);
	float denominator = toFixedInt(tanf(toFloat(angle)));
	fixedInt yScale = fixedInt_divide(numerator, denominator);
	fixedInt xScale = fixedInt_divide(yScale, aspect);
	fixedInt zScale = fixedInt_divide(far, fixedInt_subtract(far, near));
	
	camera->project.m00 = xScale;
	camera->project.m11 = yScale;
	camera->project.m22 = zScale;
	camera->project.m23 = toFixedInt(1.0f);
	camera->project.m32 = fixedInt_multiply(-near, zScale); //same as near * far / (near - far), just multiplied top and bottom by -1
	camera->project.m33 = toFixedInt(0.0f);
}

void fixedCamera_look_at(fixedCamera *camera, const fixedInt3 eye, const fixedInt3 center, const fixedInt3 up)
{
	fixedInt3 zAxis = fixedInt3_normalize(fixedInt3_subtract(center, eye));
	fixedInt3 xAxis = fixedInt3_normalize(fixedInt3_cross(up, zAxis));
	fixedInt3 yAxis = fixedInt3_cross(zAxis, xAxis);
	
	camera->view.m00 = xAxis.x;
	camera->view.m10 = xAxis.y;
	camera->view.m20 = xAxis.z;
	
	camera->view.m01 = yAxis.x;
	camera->view.m11 = yAxis.y;
	camera->view.m21 = yAxis.z;
	
	camera->view.m02 = zAxis.x;
	camera->view.m12 = zAxis.y;
	camera->view.m22 = zAxis.z;
	
	camera->view.m30 = -fixedInt3_dot(xAxis, eye);
	camera->view.m31 = -fixedInt3_dot(yAxis, eye);
	camera->view.m32 = -fixedInt3_dot(zAxis, eye);
	
	camera->view.m33 = toFixedInt(1.0f);
}

void fixedCamera_update_view_project(fixedCamera *camera)
{
	camera->viewProject = fixedInt4x4_multiply_fixedInt4x4(camera->project, camera->view);
}

// camera

void camera_perspective(camera *camera, const float fovy, const float aspect, const float near, const float far)
{
	float angle  = 0.5f * fovy * 3.14159265358979323846264338327950288f / 180.0f; // radians
	
	float numerator = 1.0f;
	float denominator = tanf(angle);
	float yScale = numerator / denominator;
	float xScale = yScale / aspect;
	float zScale = far / (far -near);
	
	camera->project.m00 = xScale;
	camera->project.m11 = yScale;
	camera->project.m22 = zScale;
	camera->project.m23 = 1.0f;
	camera->project.m32 = -near * zScale; //same as near * far / (near - far), just multiplied top and bottom by -1
	camera->project.m33 = 0.0f;
}

void camera_look_at(camera *camera, const float3 eye, const float3 center, const float3 up)
{
	float3 zAxis = float3_normalize(float3_subtract(center, eye));
	float3 xAxis = float3_normalize(float3_cross(up, zAxis));
	float3 yAxis = float3_cross(zAxis, xAxis);
	
	camera->view.m00 = xAxis.x;
	camera->view.m10 = xAxis.y;
	camera->view.m20 = xAxis.z;
	
	camera->view.m01 = yAxis.x;
	camera->view.m11 = yAxis.y;
	camera->view.m21 = yAxis.z;
	
	camera->view.m02 = zAxis.x;
	camera->view.m12 = zAxis.y;
	camera->view.m22 = zAxis.z;
	
	camera->view.m30 = -float3_dot(xAxis, eye);
	camera->view.m31 = -float3_dot(yAxis, eye);
	camera->view.m32 = -float3_dot(zAxis, eye);
	
	camera->view.m33 = 1.0f;
}

void camera_update_view_project(camera *camera)
{
	camera->viewProject = float4x4_multiply_float4x4(camera->project, camera->view);
}
