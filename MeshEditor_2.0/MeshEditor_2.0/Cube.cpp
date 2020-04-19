#include "Cube.h"
using namespace std;
struct Facet;
struct Point;
class Cube;



struct IntPoint
{
	int x, y, z;
};

void Cube::createCube(const string &filename)
{
	Point *vertexes = new Point[8], startPoint;
	int m;

	cout << "Enter coordinates of the beginning point (it is a left, bottom, far point).\nX = ";
	cin >> startPoint.x;
	cout << "Y = ";
	cin >> startPoint.y;
	cout << "Z = ";
	cin >> startPoint.z;
	cout << "Enter the length of a side: ";
	cin >> this->length_of_side;	
	cout << "Enter the comment to your file: ";
	cin >> this->comment;
	

	Point vertices[] =
	{
	  {this->length_of_side, 0, 0}, {this->length_of_side, this->length_of_side, 0}, {0, this->length_of_side, 0}, {0, 0, 0}, //A, B, C, D
	  {this->length_of_side, 0, this->length_of_side}, {this->length_of_side, this->length_of_side, this->length_of_side}, {0, this->length_of_side, this->length_of_side}, {0, 0, this->length_of_side} //E, F, G, H
	};
	IntPoint triangles[] =
	{
	  {0,1,2},{2,3,0},
	  {3,4,0},{4,3,7},
	  {2,1,5},{5,6,2},
	  {1,0,5},{4,5,0},
	  {2,6,3},{7,3,6},
	  {5,4,6},{7,6,4}
	};


	this->numOfFacets = 12;
	this->facets = new Facet[this->numOfFacets];
	for (int i = 0; i < this->numOfFacets; i++)//create cube
	{
		facets[i].vertex[2] = vertices[triangles[i].x];
		facets[i].vertex[1] = vertices[triangles[i].y];
		facets[i].vertex[0] = vertices[triangles[i].z];
	}
	for (int i = 0; i < this->numOfFacets; i++)//move cube to coordinates
	{
		for (int n = 0; n < 3; n++)
		{
			facets[i].vertex[n].x += startPoint.x;
			facets[i].vertex[n].y += startPoint.y;
			facets[i].vertex[n].z += startPoint.z;
		}
	}

	this->writeFigure(facets, filename, this->numOfFacets, comment);//write cube
	delete[] facets;
}