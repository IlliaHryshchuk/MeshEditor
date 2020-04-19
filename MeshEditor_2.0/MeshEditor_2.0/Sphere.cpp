#include "Sphere.h"
using namespace std;
struct Facet;
struct Point;
class Sphere;
struct IntPoint;
class Editor;


struct IntPoint
{
	int x, y, z;
};

void Sphere::createSphere(const string &filename)
{
	Point startPoint;


	cout << "Enter coordinates of the beginning point (center).\nX = ";
	cin >> startPoint.x;
	cout << "Y = ";
	cin >> startPoint.y;
	cout << "Z = ";
	cin >> startPoint.z;
	cout << "Enter the radius: ";
	cin >> this->radius;
	for (;;)
	{
		cout << "Enter the level of smooth (1 to 5): ";
		cin >> this->smooth_level;
		if (this->smooth_level >= 1 && this->smooth_level <= 5) break;
		else { cout << "Wrong value!\n"; continue; }
	}
	cout << "Enter the comment to your file: ";
	cin >> this->comment;

	float triSide = ((4 * this->radius) / sqrt(2 * (5 + sqrt(5))))/2; //side of triangel (/2 becouse the side = 2 by default)
	const float X = 1* triSide;
	const float Z = triSide*(1 + sqrt(5)) / 2;	//The Golden Ratio/2
	const float Y = 0.f*triSide;

	facets = new Facet[20];
	this->numOfFacets = 20;
	Point vertices[] =
	{
	  {-X,Y,Z}, {X,Y,Z}, {-X,Y,-Z}, {X,Y,-Z},
	  {Y,Z,X}, {Y,Z,-X}, {Y,-Z,X}, {Y,-Z,-X},
	  {Z,X,Y}, {-Z,X, Y}, {Z,-X,Y}, {-Z,-X, Y}
	};

	IntPoint triangles[] =
	{
	  {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
	  {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
	  {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
	  {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
	};

	for (int i = 0; i < this->numOfFacets; i++)//create icosahedron
	{
		facets[i].vertex[2] = vertices[triangles[i].x];
		facets[i].vertex[1] = vertices[triangles[i].y];
		facets[i].vertex[0] = vertices[triangles[i].z];
	}

	for(int i = 1; i <= this->smooth_level; i++) //smooth figure
		facets = subdiviside(facets, triSide);

	for (int i = 0; i < this->numOfFacets; i++)//move icosahedron to coordinates
	{
		for (int n = 0; n < 3; n++)
		{
			facets[i].vertex[n].x += startPoint.x;
			facets[i].vertex[n].y += startPoint.y;
			facets[i].vertex[n].z += startPoint.z;
		}
	}

	this->writeFigure(facets, filename, this->numOfFacets, comment);//write figure

	delete[] facets;
}



Facet* Sphere::subdiviside(Facet *facets, float size)//divide every facet by 4 facets (by the midlle lines)
{
	Facet *minifacets = new Facet[this->numOfFacets*4];

	Point nv0, nv1, nv2;
	int n = 0;

	float e = (1 + sqrt(5)) / 2;
	
	for (int i = 0; i < this->numOfFacets; i++)
	{
		nv0 = (facets[i].vertex[0] + facets[i].vertex[2])*0.5;
		nv0 = this->normalizeVector(nv0);
		nv0 = nv0 * sqrt(e*e + 1)*size;
		nv1 = (facets[i].vertex[0] + facets[i].vertex[1])*0.5;
		nv1 = this->normalizeVector(nv1);
		nv1 = nv1 * sqrt(e*e + 1) *size;
		nv2 = (facets[i].vertex[1] + facets[i].vertex[2])*0.5;
		nv2 = this->normalizeVector(nv2);
		nv2 = nv2 * sqrt(e*e + 1) *size;

		minifacets[n].vertex[0] = facets[i].vertex[0];
		minifacets[n].vertex[1] = nv1;
		minifacets[n].vertex[2] = nv0;
		minifacets[n].normal = getNormalOfTriangel(minifacets[n]);
		n++;
		minifacets[n].vertex[0] = facets[i].vertex[1];
		minifacets[n].vertex[1] = nv2;
		minifacets[n].vertex[2] = nv1;
		minifacets[n].normal = getNormalOfTriangel(minifacets[n]);
		n++;
		minifacets[n].vertex[0] = facets[i].vertex[2];
		minifacets[n].vertex[1] = nv0;
		minifacets[n].vertex[2] = nv2;
		minifacets[n].normal = getNormalOfTriangel(minifacets[n]);
		n++;
		minifacets[n].vertex[0] = nv0;
		minifacets[n].vertex[1] = nv1;
		minifacets[n].vertex[2] = nv2;
		minifacets[n].normal = getNormalOfTriangel(minifacets[n]);
		n++;
	}

	facets = new Facet[this->numOfFacets * 4];
	this->numOfFacets = numOfFacets * 4;
	return minifacets;
}