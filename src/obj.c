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

#include "obj.h"
#include "geometry.h"
#include <stdio.h>
#include <stdlib.h>

void obj_load(char* file, mesh* m, PlaydateAPI* pd)
{
	FILE *fp = fopen(file, "r");
	if(fp == NULL) {
		pd->system->logToConsole("obj_load: unable to open file %s", file);
		return;
	}
	
	char chunk[128];
	
	uint32_t vertexCount = 0;
	uint32_t indexCount = 0;
	
	while(fgets(chunk, sizeof(chunk), fp) != NULL)
	{
		if (chunk[0] == 'v' && chunk[1] == ' ')
		{
			vertexCount++;
		}
		else if (chunk[0] == 'f' && chunk[1] == ' ')
		{
			indexCount += 3;
		}
	}
	
	fclose(fp);

	pd->system->logToConsole("obj_load: found %u vertices and %u faces in .obj file %s", vertexCount, indexCount, file);
	
	mesh_init(m, indexCount, vertexCount);
	
	fp = fopen(file, "r");
	
	vertexCount = 0;
	indexCount = 0;
	
	while(fgets(chunk, sizeof(chunk), fp) != NULL)
	{
		if (chunk[0] == 'v' && chunk[1] == ' ')
		{
			char *ptr = strtok(&chunk[2], " ");
			uint32_t coord = 0;
			while (ptr != NULL)
			{
				switch (coord)
				{
					case 0:
						m->vertices[vertexCount].v.x = atof(ptr);
						break;
					case 1:
						m->vertices[vertexCount].v.y = atof(ptr);
						break;
					case 2:
						m->vertices[vertexCount].v.z = atof(ptr);
						break;
					default:
						pd->system->logToConsole("obj_load: undexpected number of vertices in %s at vertex %u", file, vertexCount);
						return;
					
				}
				coord++;
			}
			vertexCount++;
		}
		else if (chunk[0] == 'f' && chunk[1] == ' ')
		{
			char *ptr = strtok(&chunk[2], " ");
			while (ptr != NULL)
			{
				m->indices[indexCount] = atoi(ptr);
				indexCount++;
			}
		}
	}
	
	
}
