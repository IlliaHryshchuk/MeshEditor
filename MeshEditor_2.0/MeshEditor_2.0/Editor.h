#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Editor;
struct Facet;
struct Point;
class Cube;
class Sphere;
class Split;


struct Point
{
	float x, y, z;


	Point& operator = (const Point &point)
	{
		this->x = point.x;
		this->y = point.y;
		this->z = point.z;
		return *this;
	}
	Point operator + (const Point &point)
	{
		Point tmp;
		tmp.x = this->x + point.x;
		tmp.y = this->y + point.y;
		tmp.z = this->z + point.z;
		return tmp;
	}
	Point operator - (const Point &point)
	{
		Point tmp;
		tmp.x = this->x - point.x;
		tmp.y = this->y - point.y;
		tmp.z = this->z - point.z;
		return tmp;
	}
	Point operator / (const float num)
	{
		Point tmp;
		tmp.x = this->x / num;
		tmp.y = this->y / num;
		tmp.z = this->z / num;
		return tmp;
	}
	Point operator * (const float num)
	{
		Point tmp;
		tmp.x = this->x * num;
		tmp.y = this->y * num;
		tmp.z = this->z * num;
		return tmp;
	}
	//Point() 
	//{
	//	this->x = 0;
	//	this->y = 0;
	//	this->z = 0;
	//}
};


struct Facet
{
	Point normal;
	Point vertex[3];
	Facet()
	{
		this->normal.x = 0;
		this->normal.y = 0;
		this->normal.z = 0;
	}
};


class Editor
{
public: 
	Editor() {};
	void initiateCube(const string &filename);
	void initiateSphere(const string &filename);
	void initiateSplit(const string &filename);
	Facet* readFigure(const string &filename);
	void writeFigure(const Facet *facets, const string &filename, int numOfFacets, string comment);
	void writeFigure(const Facet *facets, const string &filename, int numOfFacets, string comment, bool writebegin, bool writeend);
	Point getNormalOfTriangel(const Facet &triangel);
	Point normalizeVector(Point p1);


protected:
	string comment;
	int numOfFacets;


private:
	Cube *cube;
	Sphere *sphere;
	Split *split;
};