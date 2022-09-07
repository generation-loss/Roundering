//
//  math.c
//  roundering
//
//  Created by Russell Warneboldt on 2022-09-06.
//

#include "math.h"

float3 float3_subtract(float3 a, float3 b)
{
	float3 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return result;
}

float float3_dot(float3 a, float3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float float3_length(float3 v)
{
	return sqrtf(float3_dot(v, v));
}

float3 float3_normalize(float3 unnormalized)
{
	float length = float3_length(unnormalized);
	
	float3 normalized;
	normalized.x = unnormalized.x / length;
	normalized.y = unnormalized.y / length;
	normalized.z = unnormalized.z / length;
	return normalized;
}

float3 float3_cross(float3 a, float3 b)
{
	float3 cross;
	cross.x = (a.y * b.z) - (a.z * b.y);
	cross.x = (a.z * b.x) - (a.x * b.z);
	cross.x = (a.x * b.y) - (a.y * b.x);
	return cross;
}

void Perspective(camera *camera, const float fovy, const float aspect, const float near, const float far)
{
	float angle  = (0.5f * fovy) * (float)M_PI / 180.0f; // radians
	float yScale = 1.0f / tanf(angle);
	float xScale = yScale / aspect;
	float zScale = far / (far - near);
	
	camera->view.m00 = xScale;
	camera->view.m11 = yScale;
	camera->view.m22 = zScale;
	camera->view.m23 = 1.0f;
	camera->view.m32 = -near * zScale; //same as near * far / (near - far), just multiplied top and bottom by -1
	camera->view.m33 = 0.0f;
}

void LookAt(camera *camera, const float3 eye, const float3 center, const float3 up)
{
	float3 zAxis = float3_normalize(float3_subtract(center, eye));
	float3 xAxis = float3_normalize(float3_cross(up, zAxis));
	float3 yAxis = float3_cross(zAxis, xAxis);
	
	camera->project.m00 = xAxis.x;
	camera->project.m10 = xAxis.y;
	camera->project.m20 = xAxis.z;
	
	camera->project.m01 = yAxis.x;
	camera->project.m11 = yAxis.y;
	camera->project.m21 = yAxis.z;
	
	camera->project.m02 = zAxis.x;
	camera->project.m12 = zAxis.y;
	camera->project.m22 = zAxis.z;
	
	camera->project.m30 = -float3_dot(xAxis, eye);
	camera->project.m31 = -float3_dot(yAxis, eye);
	camera->project.m32 = -float3_dot(zAxis, eye);
}
