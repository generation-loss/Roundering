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

#ifndef __ROUNDERING_GEOMETRY_H__
#define __ROUNDERING_GEOMETRY_H__

#include "math.h"

#define USE_INDEXED_GEOMETRY (1)

typedef struct vertex
{
	float3 v;
	float3 n;
} vertex;

#if !USE_INDEXED_GEOMETRY
typedef struct triangle
{
	union
	{
		struct
		{
			vertex v0;
			vertex v1;
			vertex v2;
		};
		vertex vertices[3];
	};
} triangle;
#endif

typedef struct mesh
{
#if USE_INDEXED_GEOMETRY
	uint32_t indexCount;
	uint32_t* indices;
	uint32_t vertexCount;
	vertex* vertices;
#else
	uint32_t triangleCount;
	triangle* triangles;
#endif
} mesh;

#if USE_INDEXED_GEOMETRY
static inline void mesh_init(mesh* m, uint32_t indexCount, uint32_t vertexCount)
{
	m->indexCount = indexCount;
	m->indices = malloc(sizeof(uint32_t) * indexCount);
	m->vertexCount = vertexCount;
	m->vertices = malloc(sizeof(vertex) * vertexCount);
}
#else
static inline void mesh_init(mesh* m, uint32_t triangleCount)
{
	m->triangleCount = triangleCount;
	m->triangles = malloc(sizeof(triangle) * triangleCount);
}
#endif

#endif /* __ROUNDERING_GEOMETRY_H__ */



