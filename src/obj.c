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
#include <stdlib.h>

void obj_load(char* path, mesh* m, PlaydateAPI* pd)
{
	SDFile *sd = pd->file->open(path, kFileRead);
	if(sd == NULL) {
		pd->system->logToConsole("obj_load: unable to open file %s", path);
		return;
	}
	
	char* buffer = malloc(1000000);
	const int length = pd->file->read(sd, buffer, 1000000);
	
	pd->file->close(sd);
	
	uint32_t location = 0;
	uint32_t vertexCount = 0;
	uint32_t indexCount = 0;
	
	while(location < length)
	{
		if (buffer[location] == 'v')// && buffer[location + 1] == ' ')
		{
			vertexCount++;
		}
		else if (buffer[location] == 'f')// && buffer[location + 1] == ' ')
		{
			indexCount += 3;
		}
		location++;
	}
	
	pd->system->logToConsole("obj_load: found %u vertices and %u faces in .obj file %s", vertexCount, indexCount / 3, path);
	
	mesh_init(m, indexCount, vertexCount);
	
	location = 0;
	vertexCount = 0;
	indexCount = 0;
	
	char strtokBuffer[256];
	
	while(location < length)
	{
		if (buffer[location] == 'v')// && (buffer[location + 1] == ' '))
		{
			char *line = &buffer[location + 2];
			char *newLine = strchr(line, '\n');
			
			int lineLength = newLine - line;
			memcpy(strtokBuffer, line, lineLength);
			strtokBuffer[lineLength] = '\n';
			
			char *ptr = strtok(strtokBuffer, " ");
			
			uint32_t coord = 0;
			while (coord < 3)
			{
				if (ptr == NULL)
				{
					pd->system->logToConsole("obj_load: unexpectedly few values in vertex %u for file %s", vertexCount, path);
				}
				switch (coord)
				{
					case 0:
						m->vertices[vertexCount].v.x = atof(ptr);
						//pd->system->logToConsole("obj_load: vertexCount x %u %0.2f", vertexCount, m->vertices[vertexCount].v.x);
						break;
					case 1:
						m->vertices[vertexCount].v.y = atof(ptr);
						//pd->system->logToConsole("obj_load: vertexCount y %u %0.2f", vertexCount, m->vertices[vertexCount].v.y);
						break;
					case 2:
						m->vertices[vertexCount].v.z = atof(ptr);
						//pd->system->logToConsole("obj_load: vertexCount z %u %0.2f", vertexCount, m->vertices[vertexCount].v.z);//
						break;
					
				}
				coord++;
				ptr = strtok(NULL, " ");
			}
			vertexCount++;
			strtok(strtokBuffer, "reset");
		}
		else if (buffer[location] == 'f')// && (buffer[location + 1] == ' '))
		{
			char *line = &buffer[location + 2];
			char *newLine = strchr(line, '\n');
			
			int lineLength = newLine - line;
			memcpy(strtokBuffer, line, lineLength);
			strtokBuffer[lineLength] = '\n';
			
			char *ptr = strtok(strtokBuffer, " ");
			
			uint32_t index = 0;
			while (index < 3)
			{
				if (ptr == NULL)
				{
					pd->system->logToConsole("obj_load: unexpectedly few values in face %u for file %s", indexCount / 3, path);
				}
				m->indices[indexCount + index] = atoi(ptr);
				//pd->system->logToConsole("obj_load: index %u %u", indexCount + index, m->indices[indexCount + index]);
				ptr = strtok(NULL, " ");
				index++;
			}
			indexCount += 3;
			strtok(buffer, "reset");
		}
		location++;
	}
	
	free(buffer);
}


