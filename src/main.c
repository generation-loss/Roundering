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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pd_api.h"
#include "geometry.h"
#include "timer.h"

static int update(void* userdata);

pdTimer clearTimer;
pdTimer rasterizeTimer;
pdTimer ditherTimer;

int screenWidth;
int screenHeight;
int8_t *colorRenderTarget;
uint16_t *depthRenderTarget;
camera cam;
mesh m;

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
	(void)arg; // arg is currently only used for event = kEventKeyPressed

	if ( event == kEventInit )
	{
		// Note: If you set an update callback in the kEventInit handler, the system assumes the game is pure C and doesn't run any Lua code in the game
		pd->system->setUpdateCallback(update, pd);
		
		pd->display->setScale(2);
		pd->display->setRefreshRate(30.0f);
		
		pdTimer_initialize(&clearTimer);
		pdTimer_initialize(&rasterizeTimer);
		pdTimer_initialize(&ditherTimer);
		
		screenWidth = pd->display->getWidth();
		screenHeight = pd->display->getHeight();
		
		colorRenderTarget = malloc(sizeof(int8_t) * screenWidth * (screenHeight + 2)); //+2 for dithering out-of-bounds room
		depthRenderTarget = malloc(sizeof(uint16_t) * screenWidth * (screenHeight + 2)); //+2 for dithering out-of-bounds room
		
		const float fieldOfView = 60.0f;
		const float aspect = (float)screenWidth / (float)screenHeight;
		const float near = 1.0f;
		const float far = 20.0f;
		
		camera_perspective(&cam, fieldOfView, aspect, near, far);
		
		m.triangleCount = 12;
		m.triangles = malloc(sizeof(triangle) * m.triangleCount);

		m.triangles[0].vertices[0] 	= (float3){ -1.0f, +1.0f, +1.0f };
		m.triangles[0].vertices[1] 	= (float3){ +1.0f, +1.0f, +1.0f };
		m.triangles[0].vertices[2] 	= (float3){ +1.0f, -1.0f, +1.0f };
		m.triangles[1].vertices[0] 	= (float3){ +1.0f, -1.0f, +1.0f };
		m.triangles[1].vertices[1] 	= (float3){ -1.0f, -1.0f, +1.0f };
		m.triangles[1].vertices[2] 	= (float3){ -1.0f, +1.0f, +1.0f };
	
		m.triangles[2].vertices[0] 	= (float3){ +1.0f, +1.0f, +1.0f };
		m.triangles[2].vertices[1] 	= (float3){ +1.0f, +1.0f, -1.0f };
		m.triangles[2].vertices[2] 	= (float3){ +1.0f, -1.0f, -1.0f };
		m.triangles[3].vertices[0] 	= (float3){ +1.0f, -1.0f, -1.0f };
		m.triangles[3].vertices[1] 	= (float3){ +1.0f, -1.0f, +1.0f };
		m.triangles[3].vertices[2] 	= (float3){ +1.0f, +1.0f, +1.0f };
	
		m.triangles[4].vertices[0] 	= (float3){ +1.0f, +1.0f, -1.0f };
		m.triangles[4].vertices[1] 	= (float3){ -1.0f, +1.0f, -1.0f };
		m.triangles[4].vertices[2] 	= (float3){ -1.0f, -1.0f, -1.0f };
		m.triangles[5].vertices[0] 	= (float3){ -1.0f, -1.0f, -1.0f };
		m.triangles[5].vertices[1] 	= (float3){ +1.0f, -1.0f, -1.0f };
		m.triangles[5].vertices[2] 	= (float3){ +1.0f, +1.0f, -1.0f };
	
		m.triangles[6].vertices[0] 	= (float3){ -1.0f, +1.0f, -1.0f };
		m.triangles[6].vertices[1] 	= (float3){ -1.0f, +1.0f, +1.0f };
		m.triangles[6].vertices[2] 	= (float3){ -1.0f, -1.0f, +1.0f };
		m.triangles[7].vertices[0] 	= (float3){ -1.0f, -1.0f, +1.0f };
		m.triangles[7].vertices[1] 	= (float3){ -1.0f, -1.0f, -1.0f };
		m.triangles[7].vertices[2] 	= (float3){ -1.0f, +1.0f, -1.0f };
	
		m.triangles[8].vertices[0] 	= (float3){ -1.0f, +1.0f, -1.0f };
		m.triangles[8].vertices[1] 	= (float3){ +1.0f, +1.0f, -1.0f };
		m.triangles[8].vertices[2] 	= (float3){ +1.0f, +1.0f, +1.0f };
		m.triangles[9].vertices[0] 	= (float3){ +1.0f, +1.0f, +1.0f };
		m.triangles[9].vertices[1] 	= (float3){ -1.0f, +1.0f, +1.0f };
		m.triangles[9].vertices[2] 	= (float3){ -1.0f, +1.0f, -1.0f };

		m.triangles[10].vertices[0] = (float3){ -1.0f, -1.0f, +1.0f };
		m.triangles[10].vertices[1] = (float3){ +1.0f, -1.0f, +1.0f };
		m.triangles[10].vertices[2] = (float3){ +1.0f, -1.0f, -1.0f };
		m.triangles[11].vertices[0] = (float3){ +1.0f, -1.0f, -1.0f };
		m.triangles[11].vertices[1] = (float3){ -1.0f, -1.0f, -1.0f };
		m.triangles[11].vertices[2] = (float3){ -1.0f, -1.0f, +1.0f };

		m.triangles[0].normals[0]  	= (float3){  0.0f,  0.0f, -1.0f };
		m.triangles[0].normals[1]  	= (float3){  0.0f,  0.0f, -1.0f };
		m.triangles[0].normals[2]  	= (float3){  0.0f,  0.0f, -1.0f };
		m.triangles[1].normals[0]  	= (float3){  0.0f,  0.0f, -1.0f };
		m.triangles[1].normals[1]  	= (float3){  0.0f,  0.0f, -1.0f };
		m.triangles[1].normals[2]  	= (float3){  0.0f,  0.0f, -1.0f };
 
		m.triangles[2].normals[0]  	= (float3){  1.0f,  0.0f,  0.0f };
		m.triangles[2].normals[1]  	= (float3){  1.0f,  0.0f,  0.0f };
		m.triangles[2].normals[2]  	= (float3){  1.0f,  0.0f,  0.0f };
		m.triangles[3].normals[0]  	= (float3){  1.0f,  0.0f,  0.0f };
		m.triangles[3].normals[1]  	= (float3){  1.0f,  0.0f,  0.0f };
		m.triangles[3].normals[2]  	= (float3){  1.0f,  0.0f,  0.0f };
		
		m.triangles[4].normals[0]  	= (float3){  0.0f,  0.0f,  1.0f };
		m.triangles[4].normals[1]  	= (float3){  0.0f,  0.0f,  1.0f };
		m.triangles[4].normals[2]  	= (float3){  0.0f,  0.0f,  1.0f };
		m.triangles[5].normals[0]  	= (float3){  0.0f,  0.0f,  1.0f };
		m.triangles[5].normals[1]  	= (float3){  0.0f,  0.0f,  1.0f };
		m.triangles[5].normals[2]  	= (float3){  0.0f,  0.0f,  1.0f };

		m.triangles[6].normals[0]  	= (float3){ -1.0f,  0.0f,  0.0f };
		m.triangles[6].normals[1]  	= (float3){ -1.0f,  0.0f,  0.0f };
		m.triangles[6].normals[2]  	= (float3){ -1.0f,  0.0f,  0.0f };
		m.triangles[7].normals[0]  	= (float3){ -1.0f,  0.0f,  0.0f };
		m.triangles[7].normals[1]  	= (float3){ -1.0f,  0.0f,  0.0f };
		m.triangles[7].normals[2]  	= (float3){ -1.0f,  0.0f,  0.0f };

		m.triangles[8].normals[0]  	= (float3){  0.0f,  1.0f,  0.0f };
		m.triangles[8].normals[1]  	= (float3){  0.0f,  1.0f,  0.0f };
		m.triangles[8].normals[2]  	= (float3){  0.0f,  1.0f,  0.0f };
		m.triangles[9].normals[0]  	= (float3){  0.0f,  1.0f,  0.0f };
		m.triangles[9].normals[1]  	= (float3){  0.0f,  1.0f,  0.0f };
		m.triangles[9].normals[2]  	= (float3){  0.0f,  1.0f,  0.0f };
 	
		m.triangles[10].normals[0] 	= (float3){  0.0f, -1.0f,  0.0f };
		m.triangles[10].normals[1] 	= (float3){  0.0f, -1.0f,  0.0f };
		m.triangles[10].normals[2] 	= (float3){  0.0f, -1.0f,  0.0f };
		m.triangles[11].normals[0] 	= (float3){  0.0f, -1.0f,  0.0f };
		m.triangles[11].normals[1] 	= (float3){  0.0f, -1.0f,  0.0f };
		m.triangles[11].normals[2] 	= (float3){  0.0f, -1.0f,  0.0f };
	}
	
	return 0;
}

float rotation = 0.0f;

static float edgeFunction(const float2 a, const float2 b, const float2 c)
{
	return ((c.x - a.x) * (b.y - a.y)) - ((c.y - a.y) * (b.x - a.x));
}

//#define USE_TIGHT_BOUNDING_BOX (0) //19.974
#define USE_TIGHT_BOUNDING_BOX (1) //19.814

static int update(void* userdata)
{
	PlaydateAPI* pd = userdata;
	
	rotation += 0.01f;

	float3 eye 		= { sinf(rotation) * 5.0f, 5.0f, cosf(rotation) * 5.0f };
	float3 center 	= { 0.0f, 0.0f, 0.0f };
	float3 up 		= { 0.0f, 1.0f, 0.0f };
	
	float3 lightDir = { sinf(rotation) * 1.0f, 2.0f, cosf(rotation) * 3.0f };
	lightDir = float3_normalize(lightDir);
	
	camera_look_at(&cam, eye, center, up);
	camera_update_view_project(&cam);
	
	pdTimer_start(&clearTimer, pd);
	memset(colorRenderTarget, 0, sizeof(int8_t) * screenWidth * screenHeight);
	for(int i = 0; i < screenWidth * screenHeight; ++i)
	{
		depthRenderTarget[i] = 65535;
	}
	pdTimer_end(&clearTimer, "clear", pd);

	pdTimer_start(&rasterizeTimer, pd);
	for(uint32_t i = 0; i < m.triangleCount; ++i)
	{
		triangle *triangle = &m.triangles[i];
		
		float3 transformed[3];
		float2 transformed2[3];
		
		for(uint32_t v = 0; v < 3; ++v)
		{
			float4 vertex4;
			vertex4.x = triangle->vertices[v].x;
			vertex4.y = triangle->vertices[v].y;
			vertex4.z = triangle->vertices[v].z;
			vertex4.w = 1.0f;
			
			float4 transformed4 = float4x4_multiply_float4(cam.viewProject, vertex4);
			
			float4 transformed3 = float4_divide_scalar(transformed4, transformed4.w);
			
			transformed[v].x = (transformed3.x * 0.5f + 0.5f) * screenWidth;
			transformed[v].y = (transformed3.y * 0.5f + 0.5f) * screenHeight;
			transformed[v].z = transformed3.z;
			
			transformed2[v] = float3_xy(transformed[v]);
		}
				
		float ambient = 0.1f;
		
		int bbMinY = int_clamp(floorf(float_min(transformed[0].y, float_min(transformed[1].y, transformed[2].y))), 0, screenHeight - 1);
		int bbMaxY = int_clamp( ceilf(float_max(transformed[0].y, float_max(transformed[1].y, transformed[2].y))), 0, screenHeight - 1);
		
	#if !USE_TIGHT_BOUNDING_BOX
		int bbMinX = int_clamp(floorf(float_min(transformed[0].x, float_min(transformed[1].x, transformed[2].x))), 0, screenWidth - 1);
		int bbMaxX = int_clamp( ceilf(float_max(transformed[0].x, float_max(transformed[1].x, transformed[2].x))), 0, screenWidth - 1);
	#else
		
		//x = ym + b, as we are solving for x
		const float m[3] = {
			 (transformed[1].x - transformed[0].x) / (transformed[1].y - transformed[0].y),
			 (transformed[2].x - transformed[1].x) / (transformed[2].y - transformed[1].y),
			 (transformed[0].x - transformed[2].x) / (transformed[0].y - transformed[2].y)
		};
		
		const float b[3] = {
			transformed[0].x - m[0] * transformed[0].y,
			transformed[1].x - m[1] * transformed[1].y,
			transformed[2].x - m[2] * transformed[2].y
		};
		
		const float yMin[3] = {
			float_min(transformed[0].y, transformed[1].y),
			float_min(transformed[1].y, transformed[2].y),
			float_min(transformed[2].y, transformed[0].y)
		};
		
		const float yMax[3] = {
			float_max(transformed[0].y, transformed[1].y),
			float_max(transformed[1].y, transformed[2].y),
			float_max(transformed[2].y, transformed[0].y)
		};
	
	#endif
		
		for(int y = bbMinY; y <= bbMaxY; ++y)
		{
		#if USE_TIGHT_BOUNDING_BOX
			const float x[3] = {
				(float)y * m[0] + b[0],
				(float)y * m[1] + b[1],
				(float)y * m[2] + b[2]
			};
			
			//make sure y is in range
			const bool valid[3] = {
				(y >= yMin[0]) && (y <= yMax[0]),
				(y >= yMin[1]) && (y <= yMax[1]),
				(y >= yMin[2]) && (y <= yMax[2])
			};
			
			const int bbMinX = int_clamp((int)floorf(float_min(valid[0] ? x[0] : +10000000.0f, float_min(valid[1] ? x[1] : +10000000.0f, valid[2] ? x[2] : +10000000.0f))), 0, screenWidth - 1);
			const int bbMaxX = int_clamp((int) ceilf(float_max(valid[0] ? x[0] : +10000000.0f, float_max(valid[1] ? x[1] : +10000000.0f, valid[2] ? x[2] : +10000000.0f))), 0, screenWidth - 1);
		#endif
			
			for(int x = bbMinX; x <= bbMaxX; ++x)
			{
				float2 p;
				p.x = (float)x;
				p.y = (float)y;
			
				//TODO fix inversion
				float e0 = -edgeFunction(transformed2[0], transformed2[1], p);
				float e1 = -edgeFunction(transformed2[1], transformed2[2], p);
				float e2 = -edgeFunction(transformed2[2], transformed2[0], p);
			
				if ((e0 >= 0) && (e1 >= 0) && (e2 >= 0))
				{
					//barycentrics
					const float area = -edgeFunction(transformed2[0], transformed2[1], transformed2[2]);
					e0 = e0 / area;
					e1 = e1 / area;
					e2 = e2 / area;
					
					//todo fix scale?
					uint16_t depth = (uint16_t)((transformed[0].z * e0 + transformed[1].z * e1 + transformed[2].z + e2) * (1<<12));
					
					if (depth < depthRenderTarget[y * screenWidth + x])
					{
						depthRenderTarget[y * screenWidth + x] = depth;
					
						//SHADE
						float3 normal = float3_add(float3_multiply_scalar(triangle->n0, e0), float3_add(float3_multiply_scalar(triangle->n1, e1), float3_multiply_scalar(triangle->n2, e2)));
						normal = float3_normalize(normal);
					
						float nDotL = float_clamp(float3_dot(normal, lightDir), 0.0f, 1.0f);
						float lighting = ambient + nDotL;
						if (lighting > 1.0f)
						{
							lighting = 1.0f;
						}
						colorRenderTarget[y * screenWidth + x] = (int8_t)(lighting * 64.0f);
					}
				}
			}
		}
	}
	pdTimer_end(&rasterizeTimer, "rasterize", pd);
	
	//DITHER TO FRAME BUFFER
	
	#if 1
	pdTimer_start(&ditherTimer, pd);
	uint8_t *data = pd->graphics->getFrame();
	
	for(int y = 0; y < screenHeight; ++y)
	{
		for(int x = 0; x < screenWidth / 8; ++x)
		{
			uint8_t byte = 0;
			for(int b = 0; b < 8; ++b)
			{
				const int8_t origValue = colorRenderTarget[y * screenWidth + x * 8 + b];
				const int8_t ditheredValue = origValue >= 32 ? 64 : 0;
				const int8_t ditheredError = origValue - ditheredValue;
				
				colorRenderTarget[      y * screenWidth + x * 8 + b + 1] 	+= (int8_t)(ditheredError * 7 / 16);
				colorRenderTarget[(y + 1) * screenWidth + x * 8 + b - 1] 	+= (int8_t)(ditheredError * 3 / 16);
				colorRenderTarget[(y + 1) * screenWidth + x * 8 + b] 		+= (int8_t)(ditheredError * 5 / 16);
				colorRenderTarget[(y + 1) * screenWidth + x * 8 + b + 1]	+= (int8_t)(ditheredError / 16);
			
				if (ditheredValue != 0)
				{
					byte |=  (1 << (7 - b));
				}
			}
			
			data[y * LCD_ROWSIZE + x] = byte;
		}
	}
	pdTimer_end(&ditherTimer, "dither", pd);
	
	pd->graphics->markUpdatedRows(0, LCD_ROWS - 1);
	
	#endif
	
	pd->system->drawFPS(0,0);

	return 1;
}

