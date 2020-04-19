#include "Cube.h"
#include "Sphere.h"
#include "Split.h"
#include "Editor.h"
using namespace std;
class Editor;
class Cube;
class Sphere;
class Split;
struct Facet;



void Editor::initiateCube(const string &filename)
{
	this->cube = new Cube();
	this->cube->createCube(filename);
	delete this->cube;
}



void Editor::initiateSphere(const string &filename)
{
	this->sphere = new Sphere();
	this->sphere->createSphere(filename);
	delete this->sphere;
}



void Editor::initiateSplit(const string &filename)
{
	Facet *fcts = this->readFigure(filename);
	this->split = new Split(this->comment);
	this->split->splitFigure(fcts, this->numOfFacets, filename);
	delete this->split;
}



void Editor::writeFigure(const Facet *facets, const string &filename, int numOfFacets, string comment)
{
	ofstream infile;
	infile.open(filename, ios_base::trunc);
	if (infile.is_open())
	{
		infile << "solid " << comment;
		for (int m = 0; m < numOfFacets; m++)
		{
			infile << "\nfacet normal " << facets[m].normal.x << " " << facets[m].normal.y << " " << facets[m].normal.z << "\nouter loop";
			for (int n = 0; n < 3; n++)
			{
				infile << "\nvertex " << facets[m].vertex[n].x << " " << facets[m].vertex[n].y << " " << facets[m].vertex[n].z;
			}
			infile << "\nendloop\nendfacet";
		}
		infile << "\nendsolid " << comment;


		infile.close();
		cout << "\nThe " << filename << " file was created successfully!\n";
	}
	else
	{
		cout << "An error occured!\n";
	}
}



void Editor::writeFigure(const Facet *facets, const string &filename, int numOfFacets, string comment, bool writebegin, bool writeend)
{
	ofstream infile;
	if (writebegin == true)
		infile.open(filename, ios_base::trunc);
	else
		infile.open(filename, ios_base::app);
		
	if (infile.is_open())
	{
		if (writebegin == true)
			infile << "solid " << comment;
		for (int m = 0; m < numOfFacets; m++)
		{
			infile << "\nfacet normal " << facets[m].normal.x << " " << facets[m].normal.y << " " << facets[m].normal.z << "\nouter loop";
			for (int n = 0; n < 3; n++)
			{
				infile << "\nvertex " << facets[m].vertex[n].x << " " << facets[m].vertex[n].y << " " << facets[m].vertex[n].z;
			}
			infile << "\nendloop\nendfacet";
		}
		if (writeend == true)
			infile << "\nendsolid " << comment;


		infile.close();
		if (writeend == true)
			cout << "\nThe " << filename << " file was created successfully!\n";
	}
	else
	{
		cout << "An error occured!\n";
	}
}



Facet* Editor::readFigure(const string &filename)
{
	ifstream fromfile;
	fromfile.open(filename, ios::in);
	if (fromfile.is_open())
	{
		string tmpstr;
		this->numOfFacets = 0;

		while (!fromfile.eof())
		{
			getline(fromfile, tmpstr);
			this->numOfFacets++;
		}
		fromfile.clear();
		fromfile.seekg(0);

		this->numOfFacets = (this->numOfFacets - 2) / 7;
		Facet *facets = new Facet[this->numOfFacets];


		fromfile >> tmpstr;
		fromfile >> this->comment; //comment
		for (int i = 0; i < this->numOfFacets; i++)
		{
			fromfile >> tmpstr;
			fromfile>> tmpstr; //facet normal
			fromfile >> facets[i].normal.x >> facets[i].normal.y >> facets[i].normal.z; //normal x, y, z

			fromfile >> tmpstr;
			fromfile >> tmpstr; //outer loop

			fromfile >> tmpstr >> facets[i].vertex[0].x >> facets[i].vertex[0].y >> facets[i].vertex[0].z; //vertex0 x, y, z
			fromfile >> tmpstr >> facets[i].vertex[1].x >> facets[i].vertex[1].y >> facets[i].vertex[1].z; //vertex1 x, y, z
			fromfile >> tmpstr >> facets[i].vertex[2].x >> facets[i].vertex[2].y >> facets[i].vertex[2].z; //vertex2 x, y, z

			fromfile >> tmpstr;//endloop
			fromfile >> tmpstr;//endfacet	
		}

		fromfile.close();
		return facets;
	}
}



Point Editor::normalizeVector(Point p1)
{
	float length = sqrt(p1.x*p1.x + p1.y*p1.y + p1.z*p1.z);
	p1 = p1 / length;
	return p1;
}



Point Editor::getNormalOfTriangel(const Facet &triangel)
{													   
	Point normal;
	normal.x = triangel.vertex[0].y* triangel.vertex[1].z - triangel.vertex[0].z* triangel.vertex[1].y;
	normal.y = triangel.vertex[0].z* triangel.vertex[1].x - triangel.vertex[0].x* triangel.vertex[1].z;
	normal.z = triangel.vertex[0].x* triangel.vertex[1].y - triangel.vertex[0].y* triangel.vertex[1].x;
	normal = this->normalizeVector(normal);
	return normal;
}