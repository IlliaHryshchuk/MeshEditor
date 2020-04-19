#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Editor.h"
using namespace std;
class Editor;
struct Facet;
class Sphere;
class Split;

class Sphere : Editor
{
public:
	Sphere() {}
	~Sphere() { }//delete[] this->facets;}
	void createSphere(const string &filename);
	Facet* subdiviside(Facet* facets, float size);
private:
	int smooth_level;
	float radius;
	Facet *facets;
};