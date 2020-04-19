#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Editor.h"
using namespace std;
class Editor;
struct Facet;
class Cube;
class Split;

class Cube : Editor
{
public:
	Cube() {}
	~Cube() { }//delete[] this->facets;}
	void createCube(const string &filename);
private:
	float length_of_side;
	Facet *facets;
};