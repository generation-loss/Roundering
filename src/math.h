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

typedef struct int2
{
	int x;
	int y;
} int2;

int2 int2_add(int2 a, int2 b);
int2 int2_add_scalar(int2 a, float b);
int2 int2_subtract(int2 a, int2 b);
int2 int2_subtract_scalar(int2 a, float b);
int2 int2_multiply_scalar(int2 a, float b);
int2 int2_divide_scalar(int2 a, float b);
float  int2_dot(int2 a, int2 b);
float  int2_length(int2 v);

typedef struct float2
{
	float x;
	float y;
} float2;

float2 float2_add(float2 a, float2 b);
float2 float2_add_scalar(float2 a, float b);
float2 float2_subtract(float2 a, float2 b);
float2 float2_subtract_scalar(float2 a, float b);
float2 float2_multiply_scalar(float2 a, float b);
float2 float2_divide_scalar(float2 a, float b);
float  float2_dot(float2 a, float2 b);
float  float2_length(float2 v);

typedef struct float3
{
	float x;
	float y;
	float z;
} float3;

float3 float3_add(float3 a, float3 b);
float3 float3_add_scalar(float3 a, float b);
float3 float3_subtract(float3 a, float3 b);
float3 float3_subtract_scalar(float3 a, float b);
float3 float3_multiply_scalar(float3 a, float b);
float3 float3_divide_scalar(float3 a, float b);
float  float3_dot(float3 a, float3 b);
float  float3_length(float3 v);
float3 float3_normalize(float3 unnormalized);
float3 float3_cross(float3 a, float3 b);
float2 float3_xy(float3 v);

typedef struct float4
{
	float x;
	float y;
	float z;
	float w;
} float4;

float4 float4_add(float4 a, float4 b);
float4 float4_add_scalar(float4 a, float b);
float4 float4_subtract(float4 a, float4 b);
float4 float4_subtract_scalar(float4 a, float b);
float4 float4_multiply_scalar(float4 a, float b);
float4 float4_divide_scalar(float4 a, float b);
float  float4_dot(float4 a, float4 b);
float3 float4_xyz(float4 v);

typedef struct float4x4
{
    union
    {
        struct
        {
            float m00;
            float m01;
            float m02;
            float m03;
            float m10;
            float m11;
            float m12;
            float m13;
            float m20;
            float m21;
            float m22;
            float m23;
            float m30;
            float m31;
            float m32;
            float m33;
        };
        float m[16];
		float4 mm[4];
    };
} float4x4;

float4 float4x4_multiply_float4(float4x4 a, float4 b);
float4x4 float4x4_multiply_float4x4(float4x4 a, float4x4 b);

int min(int a, int b);
int max(int a, int b);
int clamp(int val, int min, int max);

typedef struct camera
{
	float4x4 view;
	float4x4 project;
	float4x4 viewProject;
} camera;

void camera_perspective(camera *camera, const float fovy, const float aspect, const float near, const float far);
void camera_look_at(camera *camera, const float3 eye, const float3 center, const float3 up);
void camera_update_view_project(camera *camera);

#endif /* __ROUNDERING_MATH_H__ */
