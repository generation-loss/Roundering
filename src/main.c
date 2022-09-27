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

static int update(void* userdata);

camera cam;
mesh m;
int screenWidth;
int screenHeight;
int8_t *colorRenderTarget;
uint16_t *depthRenderTarget;

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
		
		screenWidth = pd->display->getWidth();
		screenHeight = pd->display->getHeight();
		
		colorRenderTarget = malloc(sizeof(int8_t) * screenWidth * (screenHeight + 2)); //+2 for dithering out-of-bounds room
		depthRenderTarget = malloc(sizeof(uint16_t) * screenWidth * (screenHeight + 2)); //+2 for dithering out-of-bounds room
		
		const fixedInt fieldOfView = toFixedInt(60.0f);
		const fixedInt aspect = toFixedInt((float)screenWidth / (float)screenHeight);
		const fixedInt near = toFixedInt(1.0f);
		const fixedInt far = toFixedInt(20.0f);
		
		camera_perspective(&cam, fieldOfView, aspect, near, far);
		
		m.triangleCount = 12;
		m.triangles = malloc(sizeof(triangle) * m.triangleCount);

		m.triangles[0].vertices[0] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(+1.0f), toFixedInt(+1.0f) };
		m.triangles[0].vertices[1] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(+1.0f), toFixedInt(+1.0f) };
		m.triangles[0].vertices[2] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(-1.0f), toFixedInt(+1.0f) };
		m.triangles[1].vertices[0] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(-1.0f), toFixedInt(+1.0f) };
		m.triangles[1].vertices[1] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(-1.0f), toFixedInt(+1.0f) };
		m.triangles[1].vertices[2] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(+1.0f), toFixedInt(+1.0f) };
	
		m.triangles[2].vertices[0] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(+1.0f), toFixedInt(+1.0f) };
		m.triangles[2].vertices[1] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(+1.0f), toFixedInt(-1.0f) };
		m.triangles[2].vertices[2] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(-1.0f), toFixedInt(-1.0f) };
		m.triangles[3].vertices[0] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(-1.0f), toFixedInt(-1.0f) };
		m.triangles[3].vertices[1] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(-1.0f), toFixedInt(+1.0f) };
		m.triangles[3].vertices[2] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(+1.0f), toFixedInt(+1.0f) };
	
		m.triangles[4].vertices[0] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(+1.0f), toFixedInt(-1.0f) };
		m.triangles[4].vertices[1] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(+1.0f), toFixedInt(-1.0f) };
		m.triangles[4].vertices[2] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(-1.0f), toFixedInt(-1.0f) };
		m.triangles[5].vertices[0] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(-1.0f), toFixedInt(-1.0f) };
		m.triangles[5].vertices[1] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(-1.0f), toFixedInt(-1.0f) };
		m.triangles[5].vertices[2] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(+1.0f), toFixedInt(-1.0f) };
	
		m.triangles[6].vertices[0] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(+1.0f), toFixedInt(-1.0f) };
		m.triangles[6].vertices[1] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(+1.0f), toFixedInt(+1.0f) };
		m.triangles[6].vertices[2] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(-1.0f), toFixedInt(+1.0f) };
		m.triangles[7].vertices[0] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(-1.0f), toFixedInt(+1.0f) };
		m.triangles[7].vertices[1] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(-1.0f), toFixedInt(-1.0f) };
		m.triangles[7].vertices[2] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(+1.0f), toFixedInt(-1.0f) };
	
		m.triangles[8].vertices[0] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(+1.0f), toFixedInt(-1.0f) };
		m.triangles[8].vertices[1] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(+1.0f), toFixedInt(-1.0f) };
		m.triangles[8].vertices[2] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(+1.0f), toFixedInt(+1.0f) };
		m.triangles[9].vertices[0] 	= (fixedInt3){ toFixedInt(+1.0f), toFixedInt(+1.0f), toFixedInt(+1.0f) };
		m.triangles[9].vertices[1] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(+1.0f), toFixedInt(+1.0f) };
		m.triangles[9].vertices[2] 	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(+1.0f), toFixedInt(-1.0f) };

		m.triangles[10].vertices[0] = (fixedInt3){ toFixedInt(-1.0f), toFixedInt(-1.0f), toFixedInt(+1.0f) };
		m.triangles[10].vertices[1] = (fixedInt3){ toFixedInt(+1.0f), toFixedInt(-1.0f), toFixedInt(+1.0f) };
		m.triangles[10].vertices[2] = (fixedInt3){ toFixedInt(+1.0f), toFixedInt(-1.0f), toFixedInt(-1.0f) };
		m.triangles[11].vertices[0] = (fixedInt3){ toFixedInt(+1.0f), toFixedInt(-1.0f), toFixedInt(-1.0f) };
		m.triangles[11].vertices[1] = (fixedInt3){ toFixedInt(-1.0f), toFixedInt(-1.0f), toFixedInt(-1.0f) };
		m.triangles[11].vertices[2] = (fixedInt3){ toFixedInt(-1.0f), toFixedInt(-1.0f), toFixedInt(+1.0f) };

		m.triangles[0].normals[0]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(-1.0f) };
		m.triangles[0].normals[1]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(-1.0f) };
		m.triangles[0].normals[2]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(-1.0f) };
		m.triangles[1].normals[0]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(-1.0f) };
		m.triangles[1].normals[1]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(-1.0f) };
		m.triangles[1].normals[2]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(-1.0f) };
 
		m.triangles[2].normals[0]  	= (fixedInt3){ toFixedInt( 1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		m.triangles[2].normals[1]  	= (fixedInt3){ toFixedInt( 1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		m.triangles[2].normals[2]  	= (fixedInt3){ toFixedInt( 1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		m.triangles[3].normals[0]  	= (fixedInt3){ toFixedInt( 1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		m.triangles[3].normals[1]  	= (fixedInt3){ toFixedInt( 1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		m.triangles[3].normals[2]  	= (fixedInt3){ toFixedInt( 1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		
		m.triangles[4].normals[0]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(1.0f) };
		m.triangles[4].normals[1]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(1.0f) };
		m.triangles[4].normals[2]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(1.0f) };
		m.triangles[5].normals[0]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(1.0f) };
		m.triangles[5].normals[1]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(1.0f) };
		m.triangles[5].normals[2]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(0.0f),  toFixedInt(1.0f) };

		m.triangles[6].normals[0]  	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		m.triangles[6].normals[1]  	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		m.triangles[6].normals[2]  	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		m.triangles[7].normals[0]  	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		m.triangles[7].normals[1]  	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };
		m.triangles[7].normals[2]  	= (fixedInt3){ toFixedInt(-1.0f), toFixedInt(0.0f),  toFixedInt(0.0f) };

		m.triangles[8].normals[0]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(1.0f),  toFixedInt(0.0f) };
		m.triangles[8].normals[1]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(1.0f),  toFixedInt(0.0f) };
		m.triangles[8].normals[2]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(1.0f),  toFixedInt(0.0f) };
		m.triangles[9].normals[0]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(1.0f),  toFixedInt(0.0f) };
		m.triangles[9].normals[1]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(1.0f),  toFixedInt(0.0f) };
		m.triangles[9].normals[2]  	= (fixedInt3){ toFixedInt( 0.0f), toFixedInt(1.0f),  toFixedInt(0.0f) };
 	
		m.triangles[10].normals[0] 	= (fixedInt3){ toFixedInt(0.0f), toFixedInt(-1.0f), toFixedInt(0.0f) };
		m.triangles[10].normals[1] 	= (fixedInt3){ toFixedInt(0.0f), toFixedInt(-1.0f), toFixedInt(0.0f) };
		m.triangles[10].normals[2] 	= (fixedInt3){ toFixedInt(0.0f), toFixedInt(-1.0f), toFixedInt(0.0f) };
		m.triangles[11].normals[0] 	= (fixedInt3){ toFixedInt(0.0f), toFixedInt(-1.0f), toFixedInt(0.0f) };
		m.triangles[11].normals[1] 	= (fixedInt3){ toFixedInt(0.0f), toFixedInt(-1.0f), toFixedInt(0.0f) };
		m.triangles[11].normals[2] 	= (fixedInt3){ toFixedInt(0.0f), toFixedInt(-1.0f), toFixedInt(0.0f) };
	}
	
	return 0;
}

float rotation = 0.0f;

static fixedInt edgeFunction(const fixedInt2 a, const fixedInt2 b, const fixedInt2 c)
{
	fixedInt x = fixedInt_subtract(c.x, a.x);
	fixedInt y = fixedInt_subtract(b.y, a.y);
	fixedInt z = fixedInt_subtract(c.y, a.y);
	fixedInt w = fixedInt_subtract(b.x, a.x);
    return fixedInt_subtract(fixedInt_multiply(x, y), fixedInt_multiply(z, w));
}

static int update(void* userdata)
{
	PlaydateAPI* pd = userdata;
	
	rotation += 0.01f;

	fixedInt3 eye 		= { toFixedInt(sinf(rotation) * 5.0f), toFixedInt(5.0f), toFixedInt(cosf(rotation) * 5.0f) };
	fixedInt3 center 	= { toFixedInt(0.0f), toFixedInt(0.0f), toFixedInt(0.0f) };
	fixedInt3 up 		= { toFixedInt(0.0f), toFixedInt(1.0f), toFixedInt(0.0f) };
	
	fixedInt3 lightDir = { toFixedInt(sinf(rotation) * 1.0f), toFixedInt(2.0f), toFixedInt(cosf(rotation) * 3.0f) };
	lightDir = fixedInt3_normalize(lightDir);
	
	camera_look_at(&cam, eye, center, up);
	camera_update_view_project(&cam);
	
	#if 1
	float before = pd->system->getElapsedTime();
	memset(colorRenderTarget, 0, sizeof(int8_t) * screenWidth * screenHeight);
	float after = pd->system->getElapsedTime() - before;
	pd->system->logToConsole("Color render target clear: %0.3f milliseconds", after * 1000.0f);
	#endif
	#if 1
	before = pd->system->getElapsedTime();
	for(int i = 0; i < screenWidth * screenHeight; ++i)
	{
		depthRenderTarget[i] = FIXED_INT_SCALE;
	}
	after = pd->system->getElapsedTime() - before;
	pd->system->logToConsole("Depth render target clear: %0.3f milliseconds", after * 1000.0f);
	#endif

#if 1
	for(uint32_t i = 0; i < m.triangleCount; ++i)
	{
		triangle *triangle = &m.triangles[i];
		
		fixedInt3 transformed[3];
		fixedInt2 transformed2[3];
		
		for(uint32_t v = 0; v < 3; ++v)
		{
			fixedInt4 vertex4;
			vertex4.x = triangle->vertices[v].x;
			vertex4.y = triangle->vertices[v].y;
			vertex4.z = triangle->vertices[v].z;
			vertex4.w = toFixedInt(1.0f);
			
			fixedInt4 transformed4 = fixedInt4x4_multiply_fixedInt4(cam.viewProject, vertex4);
			
			fixedInt4 transformed3 = fixedInt4_divide_scalar(transformed4, transformed4.w);
			
			transformed[v].x = fixedInt_multiply(fixedInt_add(fixedInt_multiply(transformed3.x, toFixedInt(0.5f)), toFixedInt(0.5f)), toFixedInt(screenWidth));
			transformed[v].y = fixedInt_multiply(fixedInt_add(fixedInt_multiply(transformed3.y, toFixedInt(0.5f)), toFixedInt(0.5f)), toFixedInt(screenHeight));
			transformed[v].z = transformed3.z;
			
			transformed2[v] = fixedInt3_xy(transformed[v]);
		}
				
		float ambient = 0.1f;
		
		int bbMinX = (int)floorf(toFloat(fixedInt_min(transformed[0].x, fixedInt_min(transformed[1].x, transformed[2].x))));// int_min( (int)(floorf(toFloat(transformed[0].x))), int_min( (int)(floorf(toFloat(transformed[1].x))), (int)(floorf(toFloat(transformed[2].x))) ) );
		int bbMinY = (int)floorf(toFloat(fixedInt_min(transformed[0].y, fixedInt_min(transformed[1].y, transformed[2].y))));// int_min( (int)(floorf(toFloat(transformed[0].y))), int_min( (int)(floorf(toFloat(transformed[1].y))), (int)(floorf(toFloat(transformed[2].y))) ) );
		
		int bbMaxX = (int)ceilf(toFloat(fixedInt_max(transformed[0].x, fixedInt_max(transformed[1].x, transformed[2].x))));// int_max( (int)(floorf(toFloat(transformed[0].x))), int_max( (int)(floorf(toFloat(transformed[1].x))), (int)(floorf(toFloat(transformed[2].x))) ) );
		int bbMaxY = (int)ceilf(toFloat(fixedInt_max(transformed[0].y, fixedInt_max(transformed[1].y, transformed[2].y))));// int_max( (int)(floorf(toFloat(transformed[0].y))), int_max( (int)(floorf(toFloat(transformed[1].y))), (int)(floorf(toFloat(transformed[2].y))) ) );
		
		for(int y = bbMinY; y <= bbMaxY; ++y)
		{
			for(int x = bbMinX; x <= bbMaxX; ++x)
			{
				fixedInt2 p;
				p.x = toFixedInt((float)x);
				p.y = toFixedInt((float)y);
			
				//TODO fix inversion
				fixedInt e0 = -edgeFunction(transformed2[0], transformed2[1], p);
				fixedInt e1 = -edgeFunction(transformed2[1], transformed2[2], p);
				fixedInt e2 = -edgeFunction(transformed2[2], transformed2[0], p);
				
				if ((e0 >= 0) && (e1 >= 0) && (e2 >= 0))
				{
					//barycentrics
					fixedInt area = -edgeFunction(transformed2[0], transformed2[1], transformed2[2]);
					e0 = fixedInt_divide(e0, area);
					e1 = fixedInt_divide(e1, area);
					e2 = fixedInt_divide(e2, area);
					
					//todo scale?
					uint16_t depth = (uint16_t)((fixedInt_multiply(transformed[0].z, e0)) + (fixedInt_multiply(transformed[1].z, e1)) + (fixedInt_multiply(transformed[2].z, e2)));
					
					if (depth < depthRenderTarget[y * screenWidth + x])
					{
						depthRenderTarget[y * screenWidth + x] = depth;
					
						//SHADE
						fixedInt3 normal = fixedInt3_add(fixedInt3_multiply_scalar(triangle->n0, e0), fixedInt3_add(fixedInt3_multiply_scalar(triangle->n1, e1), fixedInt3_multiply_scalar(triangle->n2, e2)));
						normal = fixedInt3_normalize(normal);
					
						float nDotL = toFloat(fixedInt_clamp(fixedInt3_dot(normal, lightDir), toFixedInt(0), toFixedInt(1)));
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
#endif
	
	//COPY TO FRAME BUFFER
	
	#if 1
	before = pd->system->getElapsedTime();
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
	after = pd->system->getElapsedTime() - before;
	pd->system->logToConsole("dither: %0.3f milliseconds", after * 1000.0f);
	
	pd->graphics->markUpdatedRows(0, LCD_ROWS - 1);
	
	#endif
	
	pd->system->drawFPS(0,0);

	return 1;
}

