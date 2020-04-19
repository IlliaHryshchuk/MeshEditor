#pragma once
#include <iostream>
#include "Editor.h"
using namespace std;
class Editor;
struct Facet;
class Cube;
class Sphere;



class Split : Editor
{
public:
	Split() { splittingPlane = new Point[3]; }
	Split(string str) { this->comment = str; splittingPlane = new Point[3]; }
	~Split() { delete[] this->splittingPlane;}
	void splitFigure(Facet* facets, int numOfFacets, const string &filename);//main function
private:
	Point* splittingPlane;
	float A, B, C, D;

	Point* getSplittingPlane(Point* splittingPlane); //enter the splitting plane
	float getLocOfPointRelativelyToPlane(Point M); //higher or lower or on
	Point getIntersectPoint_LineAndPlane(Point M1, Point M2); //intersection of line and plane
	bool isPointInLine(Point point, Point A, Point B); //is point lays in line AB
	float getDistanceBetween2Points(Point A, Point B);

};