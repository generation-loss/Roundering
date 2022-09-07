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

#include "pd_api.h"

static int update(void* userdata);

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
		
		pd->display->setRefreshRate(30.0f);
	}
	
	return 0;
}

int curBit = 0;

static int update(void* userdata)
{
	PlaydateAPI* pd = userdata;
	
	LCDBitmap* bitmap = pd->graphics->getDisplayBufferBitmap();
	
	int width;
	int height;
	int rowBytes;
	uint8_t *mask;
	uint8_t *data;
	
	pd->graphics->getBitmapData(bitmap, &width, &height, &rowBytes, &mask, &data);
	
	data = pd->graphics->getFrame();
	
	const int size = width * height;
	
	for (int x = 0; x < width / 8; ++x)
	{
		for (int y = 0; y < height; ++y)
		{
			int bit = y * width + x * 8;
			
			uint8_t val = 0;
			
			for(int b = 0; b < 8; ++b)
			{
				int invB = 7-b;
				if (bit + b < curBit)
				{
					val |= 1 << invB;
				}
				else
				{
					val &= ~(1 << invB);
				}
			}
			
			data[y * rowBytes + x] = val;
		}
	}
	
	curBit = (curBit + 1) % size;
	
	pd->graphics->markUpdatedRows(0, LCD_ROWS - 1);
	
	pd->system->drawFPS(0,0);

	return 1;
}

