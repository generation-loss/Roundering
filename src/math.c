//
//  math.c
//  roundering
//
//  Created by Russell Warneboldt on 2022-09-06.
//

#include "math.h"

// float3

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

// float4

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

// float4x4

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

// misc

int clamp(int val, int minVal, int maxVal)
{
	int result = val;
	
	if (result < minVal)
		result = minVal;
		
	if (result > maxVal)
		result = maxVal;
		
	return result;
}

// camera

void camera_perspective(camera *camera, const float fovy, const float aspect, const float near, const float far)
{
	float angle  = (0.5f * fovy) * (float)M_PI / 180.0f; // radians
	float yScale = 1.0f / tanf(angle);
	float xScale = yScale / aspect;
	float zScale = far / (far - near);
	
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
}

void camera_update_view_project(camera *camera)
{
	camera->viewProject = float4x4_multiply_float4x4(camera->project, camera->view);
}
