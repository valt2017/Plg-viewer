#pragma once
#include <GL/glut.h>
#include <vector>

struct vertex
{
	GLdouble x, y, z;
};

typedef std::vector<vertex> Poly;

struct Plg
{
	std::string Name;
	std::vector<Poly> PolygonList;
	bool Load(const char * fileName);
};

