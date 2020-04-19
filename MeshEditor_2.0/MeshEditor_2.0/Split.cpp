#include "Split.h"
#include <math.h>
#include <vector>
//#include <algorithm>
using namespace std;
struct Facet;
struct Point;
class Split;



bool is3PointsOnOneLine(Point p1, Point p2, Point p3)
{
	float r1 = (p3.x - p1.x) / (p2.x - p1.x);
	float r2 = (p3.y - p1.y) / (p2.y - p1.y);
	float r3 = (p3.z - p1.z) / (p2.z - p1.z);

	if ((abs(p1.x - p2.x) <= 0.01) && (abs(p1.x - p3.x) <= 0.01) && (abs(p2.x - p3.x) <= 0.01)) return true;
	if ((abs(p1.y - p2.y) <= 0.01) && (abs(p1.y - p3.y) <= 0.01) && (abs(p2.y - p3.y) <= 0.01)) return true;
	if ((abs(p1.z - p2.z) <= 0.01) && (abs(p1.z - p3.z) <= 0.01) && (abs(p2.z - p3.z) <= 0.01)) return true;

	if ((abs(r1 - r2) <= 0.01) && (abs(r1 - r3) <= 0.01)) return true;
	else return false;
}




void quickSort(vector<Point>& arr, int left, int right)
{
	int i = left, j = right;
	Point tmp;
	float pivot = arr[(left + right) / 2].x;

	while (i <= j) {
		while (arr[i].x < pivot)
			i++;
		while (arr[j].x > pivot)
			j--;
		if (i <= j) 
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);

}




Point* Split::getSplittingPlane(Point* splittingPlane)
{
	cout << "The figure will be splited by the plane. Enter 3 points of the plane:\n";
	for (int i = 0; i < 3; i++)
	{
		cout << "M" << i << ".x = ";
		cin >> splittingPlane[i].x;
		cout << "M" << i << ".y = ";
		cin >> splittingPlane[i].y;
		cout << "M" << i << ".z = ";
		cin >> splittingPlane[i].z;
		cout << endl;
	}

	//splittingPlane[0].x = -100;
	//splittingPlane[0].y = -96;
	//splittingPlane[0].z = -114;
	//splittingPlane[1].x = 103;
	//splittingPlane[1].y = 117;
	//splittingPlane[1].z = 124;
	//splittingPlane[2].x = -110;
	//splittingPlane[2].y = 133;
	//splittingPlane[2].z = 86;


	//Equation of a plane: Ax + By + Cz + D = 0
	this->A = (splittingPlane[1].y - splittingPlane[0].y)*(splittingPlane[2].z - splittingPlane[0].z) - (splittingPlane[2].y - splittingPlane[0].y)*(splittingPlane[1].z - splittingPlane[0].z);
	this->B = -1 * ((splittingPlane[1].x - splittingPlane[0].x)*(splittingPlane[2].z - splittingPlane[0].z) - (splittingPlane[2].x - splittingPlane[0].x)*(splittingPlane[1].z - splittingPlane[0].z));
	this->C = (splittingPlane[1].x - splittingPlane[0].x)*(splittingPlane[2].y - splittingPlane[0].y) - (splittingPlane[2].x - splittingPlane[0].x)*(splittingPlane[1].y - splittingPlane[0].y);
	this->D = splittingPlane[0].y*((splittingPlane[1].x - splittingPlane[0].x)*(splittingPlane[2].z - splittingPlane[0].z) - (splittingPlane[2].x - splittingPlane[0].x)*(splittingPlane[1].z - splittingPlane[0].z)) -
		splittingPlane[0].x*((splittingPlane[1].y - splittingPlane[0].y)*(splittingPlane[2].z - splittingPlane[0].z) - (splittingPlane[2].y - splittingPlane[0].y)*(splittingPlane[1].z - splittingPlane[0].z)) -
		splittingPlane[0].z*((splittingPlane[1].x - splittingPlane[0].x)*(splittingPlane[2].y - splittingPlane[0].y) - (splittingPlane[2].x - splittingPlane[0].x)*(splittingPlane[1].y - splittingPlane[0].y));

	return splittingPlane;
}



float Split::getLocOfPointRelativelyToPlane(Point M)//equation of a plane
{
	float rez = this->A*M.x + this->B*M.y + this->C*M.z + this->D;
	if (rez <= 0.5 && rez >= -0.5) rez = 0;

	return rez;
}



Point Split::getIntersectPoint_LineAndPlane(Point M1, Point M2)
{
	//Equation of a line: (x-x1)/p + (y-y1)/q + (z-z1)/t,  where p,q,t is vector: x2-x1
	float p = M2.x - M1.x;
	float q = M2.y - M1.y;
	float t = M2.z - M1.z;


	float v = - (this->D + this->A * M1.x + this->B * M1.y + this->C * M1.z) / (this->A * p + this->B * q + this->C * t);

	Point intersectionPoint;
	intersectionPoint.x = M1.x + p * v;
	intersectionPoint.y = M1.y + q * v;
	intersectionPoint.z = M1.z + t * v;


	return intersectionPoint;
}



bool Split::isPointInLine(Point point, Point A, Point B)
{
	float AB = sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2) + pow((B.z - A.z), 2));
	float pointA = sqrt(pow((A.x - point.x), 2) + pow((A.y - point.y), 2) + pow((A.z - point.z), 2));
	float pointB = sqrt(pow((B.x - point.x), 2) + pow((B.y - point.y), 2) + pow((B.z - point.z), 2));

	if (abs(AB - (pointA + pointB)) <= 0.01)  return true;
	else return false;
}



float Split::getDistanceBetween2Points(Point A, Point B)
{
	float AB = sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2) + pow((B.z - A.z), 2));
	return AB;
}



void Split::splitFigure(Facet* facets, int numOfFacets, const string &filename) //THE MAIN FUNCTION
{
	int distance = 50; //distance between 2 parts of a figure (if in one file)
	float position0 = 0, position1 = 0, position2 = 0;
	int left = 0, right = 0;//num of left and right triangels
	bool isBelong01 = false, isBelong02 = false, isBelong12 = false;
	Point m0, m1, m2;
	string file_part1 = filename.substr(0, filename.size() - 4) + "_part1.stl";
	string file_part2 = filename.substr(0, filename.size() - 4) + "_part2.stl";
	string file_solid = filename.substr(0, filename.size() - 4) + "_solid.stl", chooser;
	vector<Point> crossedPoints;


	cout << "\nYour figure is: " << filename << endl;
	this->splittingPlane = this->getSplittingPlane(this->splittingPlane);



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// count left, right, and crossed triangels
	for (int i = 0; i < numOfFacets; i++)
	{
		position0 = getLocOfPointRelativelyToPlane(facets[i].vertex[0]);
		position1 = getLocOfPointRelativelyToPlane(facets[i].vertex[1]);
		position2 = getLocOfPointRelativelyToPlane(facets[i].vertex[2]);

		if ((position0 > 0) && (position1 > 0) && (position2 > 0))
		{
			left++;
		}
		else if ((position0 < 0) && (position1 < 0) && (position2 < 0))
		{
			right++;
		}
	}


	Facet* figureLeft = new Facet[left]; //allocate arrays for left, right, and crossed triangels
	Facet* figureRight = new Facet[right];
	Facet* figureMiddle = new Facet[(numOfFacets - right - left) * 3];
	Facet* planeMiddle;
	int mj = 0, fli = 0, fri = 0;



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// divide figure into two subfigures
	for (int i = 0; i < numOfFacets; i++)
	{
		isBelong01 = false;
		isBelong02 = false;
		isBelong12 = false;
		position0 = getLocOfPointRelativelyToPlane(facets[i].vertex[0]);
		position1 = getLocOfPointRelativelyToPlane(facets[i].vertex[1]);
		position2 = getLocOfPointRelativelyToPlane(facets[i].vertex[2]);

		if ((position0 > 0) && (position1 > 0) && (position2 > 0)) //higher than a plane
		{
			figureLeft[fli].vertex[0] = facets[i].vertex[0];
			figureLeft[fli].vertex[1] = facets[i].vertex[1];
			figureLeft[fli].vertex[2] = facets[i].vertex[2];
			figureLeft[fli].normal = facets[i].normal;
			fli++;
		}
		else if ((position0 < 0) && (position1 < 0) && (position2 < 0))//lower than a plane
		{
			figureRight[fri].vertex[0] = facets[i].vertex[0];
			figureRight[fri].vertex[1] = facets[i].vertex[1];
			figureRight[fri].vertex[2] = facets[i].vertex[2];
			figureRight[fri].normal = facets[i].normal;
			fri++;
		}
		else//crossed by plane
		{
			m0 = getIntersectPoint_LineAndPlane(facets[i].vertex[0], facets[i].vertex[1]); //find the cross point of sides and the plane
			isBelong01 = isPointInLine(m0, facets[i].vertex[0], facets[i].vertex[1]);

			m1 = getIntersectPoint_LineAndPlane(facets[i].vertex[1], facets[i].vertex[2]);
			isBelong12 = isPointInLine(m1, facets[i].vertex[1], facets[i].vertex[2]);

			m2 = getIntersectPoint_LineAndPlane(facets[i].vertex[0], facets[i].vertex[2]);
			isBelong02 = isPointInLine(m2, facets[i].vertex[0], facets[i].vertex[2]);


			if (isBelong01 == true && isBelong12 == true)//if plane croses left and right sides
			{
				figureMiddle[mj].vertex[0] = m0;
				figureMiddle[mj].vertex[1] = facets[i].vertex[1];
				figureMiddle[mj].vertex[2] = m1;
				figureMiddle[mj].normal = getNormalOfTriangel(figureMiddle[mj]);
				mj++;


				figureMiddle[mj].vertex[0] = facets[i].vertex[0];
				figureMiddle[mj].vertex[1] = m0;
				figureMiddle[mj].vertex[2] = m1;
				figureMiddle[mj].normal = getNormalOfTriangel(figureMiddle[mj]);
				mj++;


				figureMiddle[mj].vertex[0] = facets[i].vertex[0];
				figureMiddle[mj].vertex[1] = m1;
				figureMiddle[mj].vertex[2] = facets[i].vertex[2];
				figureMiddle[mj].normal = getNormalOfTriangel(figureMiddle[mj]);
				mj++;


				crossedPoints.push_back(m1);
				crossedPoints.push_back(m0);
			}
			else if (isBelong01 == true && isBelong02 == true)//left and bottom
			{
				figureMiddle[mj].vertex[0] = facets[i].vertex[0];
				figureMiddle[mj].vertex[1] = m0;
				figureMiddle[mj].vertex[2] = m2;
				figureMiddle[mj].normal = getNormalOfTriangel(figureMiddle[mj]);
				mj++;


				figureMiddle[mj].vertex[0] = m0;
				figureMiddle[mj].vertex[1] = facets[i].vertex[1];
				figureMiddle[mj].vertex[2] = m2;
				figureMiddle[mj].normal = getNormalOfTriangel(figureMiddle[mj]);
				mj++;


				figureMiddle[mj].vertex[0] = m2;
				figureMiddle[mj].vertex[1] = facets[i].vertex[1];
				figureMiddle[mj].vertex[2] = facets[i].vertex[2];
				figureMiddle[mj].normal = getNormalOfTriangel(figureMiddle[mj]);
				mj++;


				crossedPoints.push_back(m2);
				crossedPoints.push_back(m0);

			}
			else if (isBelong12 == true && isBelong02 == true)//right and bottom
			{
				figureMiddle[mj].vertex[0] = m2;
				figureMiddle[mj].vertex[1] = m1;
				figureMiddle[mj].vertex[2] = facets[i].vertex[2];
				figureMiddle[mj].normal = getNormalOfTriangel(figureMiddle[mj]);
				mj++;


				figureMiddle[mj].vertex[0] = m2;
				figureMiddle[mj].vertex[1] = facets[i].vertex[1];
				figureMiddle[mj].vertex[2] = m1;
				figureMiddle[mj].normal = getNormalOfTriangel(figureMiddle[mj]);
				mj++;


				figureMiddle[mj].vertex[0] = facets[i].vertex[0];
				figureMiddle[mj].vertex[1] = facets[i].vertex[1];
				figureMiddle[mj].vertex[2] = m2;
				figureMiddle[mj].normal = getNormalOfTriangel(figureMiddle[mj]);
				mj++;


				crossedPoints.push_back(m1);
				crossedPoints.push_back(m2);
			}
		}
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// create a plane
	int numOfTriangelsInPlane = (numOfFacets - right - left) - 2;//allocate array for a plane
	if (numOfTriangelsInPlane > 0)
	{

		planeMiddle = new Facet[numOfTriangelsInPlane];
		quickSort(crossedPoints, 0, crossedPoints.size() - 1); //sort the crossed points to find the righter one


		//cout << "coo_test:\n";  for (int i = 0; i < crossedPoints.size(); i++) { cout << "point_" << i << "=   " << crossedPoints[i].x << "   " << crossedPoints[i].y << "   " << crossedPoints[i].z << endl; } //for testing
		for (int i = 0; i < crossedPoints.size() - 1; i++)//delete similar points
		{
			for (int j = i + 1; j < crossedPoints.size(); j++)
			{
				if ((abs(crossedPoints[i].x - crossedPoints[j].x) <= 0.01) && (abs(crossedPoints[i].y - crossedPoints[j].y) <= 0.01) && (abs(crossedPoints[i].z - crossedPoints[j].z) <= 0.01))
				{
					crossedPoints.erase(crossedPoints.begin() + j);
					break;
				}
			}
		}
		//cout << "\nafter\n\n"; for (int i = 0; i < crossedPoints.size(); i++){cout << "point_" << i << "=   " << crossedPoints[i].x << "   " << crossedPoints[i].y << "   " << crossedPoints[i].z << endl;} //for testing


		int ii = 1;
		float dist = 0;
		float mindist = 32766;
		int remember_i = 0;


		//create firts triangel
		m0 = crossedPoints[0];
		crossedPoints.erase(crossedPoints.begin());
		for (int i = 0; i < crossedPoints.size(); i++)//find the nearest point
		{
			dist = getDistanceBetween2Points(m0, crossedPoints[i]);
			if (mindist > dist)
			{
				mindist = dist;
				remember_i = i;
			}
		}
		mindist = 32766;
		m1 = crossedPoints[remember_i];

		crossedPoints.erase(crossedPoints.begin() + remember_i);
		for (int i = 0; i < crossedPoints.size(); i++)//find the nearest point
		{
			//check if they on one line
			if (is3PointsOnOneLine(crossedPoints[i], m0, m1) == true) continue;

			dist = getDistanceBetween2Points(m0, crossedPoints[i]);
			if (mindist > dist)
			{
				mindist = dist;
				remember_i = i;
			}
		}
		mindist = 32766;
		m2 = crossedPoints[remember_i];
		crossedPoints.erase(crossedPoints.begin() + remember_i);


		planeMiddle[0].vertex[1] = m0;
		planeMiddle[0].vertex[0] = m1;
		planeMiddle[0].vertex[2] = m2;
		planeMiddle[0].normal = getNormalOfTriangel(planeMiddle[0]);



		while (crossedPoints.size() >= 3)//create other triangels
		{
			for (int i = 0; i <= crossedPoints.size()-1; i++)//find the nearest point
			{
				//check if they on one line
				if (is3PointsOnOneLine(crossedPoints[i], m1, m2) == true) continue;

				dist = getDistanceBetween2Points(m1, crossedPoints[i]);
				if (mindist > dist)
				{
					mindist = dist;
					remember_i = i;
				}
			}
			mindist = 32766;
			planeMiddle[ii].vertex[1] = m1;

			m1 = crossedPoints[remember_i];
			crossedPoints.erase(crossedPoints.begin() + remember_i);
			planeMiddle[ii].vertex[0] = m1;
			planeMiddle[ii].vertex[2] = m2;
			planeMiddle[ii].normal = getNormalOfTriangel(planeMiddle[ii]);
			ii++;


			for (int i = 0; i <= crossedPoints.size()-1; i++)//find the nearest point
			{
				//check if they on one line
				if (is3PointsOnOneLine(crossedPoints[i], m1, m2) == true) continue;

				dist = getDistanceBetween2Points(m2, crossedPoints[i]);
				if (mindist > dist)
				{
					mindist = dist;
					remember_i = i;
				}
			}
			mindist = 32766;
			planeMiddle[ii].vertex[0] = m2;

			m2 = crossedPoints[remember_i];
			crossedPoints.erase(crossedPoints.begin() + remember_i);
			planeMiddle[ii].vertex[1] = m2;
			planeMiddle[ii].vertex[2] = m1;
			planeMiddle[ii].normal = getNormalOfTriangel(planeMiddle[ii]);
			ii++;
		}


		//if there 2 points lasts
		if (crossedPoints.size() == 2)
		{
			for (int i = 0; i <= crossedPoints.size() - 1; i++)//find the nearest point
			{
				dist = getDistanceBetween2Points(m1, crossedPoints[i]);
				if (mindist > dist)
				{
					mindist = dist;
					remember_i = i;
				}
			}
			planeMiddle[ii].vertex[1] = m1;

			m1 = crossedPoints[remember_i];
			crossedPoints.erase(crossedPoints.begin() + remember_i);
			planeMiddle[ii].vertex[0] = m1;
			planeMiddle[ii].vertex[2] = m2;
			planeMiddle[ii].normal = getNormalOfTriangel(planeMiddle[ii]);
			ii++;
		}
		//create last triangel
		planeMiddle[ii].vertex[0] = m1;
		planeMiddle[ii].vertex[1] = m2;
		planeMiddle[ii].vertex[2] = crossedPoints[0];
		planeMiddle[ii].normal = getNormalOfTriangel(planeMiddle[ii]);


		if (planeMiddle[numOfTriangelsInPlane - 1].normal.x == 0 && planeMiddle[numOfTriangelsInPlane - 1].normal.y == 0 && planeMiddle[numOfTriangelsInPlane - 1].normal.z == 0) numOfTriangelsInPlane = numOfTriangelsInPlane - 1;
		if (planeMiddle[numOfTriangelsInPlane - 1].normal.x == 0 && planeMiddle[numOfTriangelsInPlane - 1].normal.y == 0 && planeMiddle[numOfTriangelsInPlane - 1].normal.z == 0) numOfTriangelsInPlane = numOfTriangelsInPlane - 1;
	}
	else
	{
		numOfTriangelsInPlane = 0;
		planeMiddle = new Facet[1];
	}




	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////writing figure into file
	cout << "\nWrite the splited parts of a figure in two separate files?\n1 - Yes, in two files | 2 - No, in one file\n";
	while (1)
	{
		cin >> chooser;
		if (chooser == "1")//////////////////////if in two files
		{
			fri = 0;
			fli = 0;
			for (int i = 0; i < ((numOfFacets - right - left) * 3); i++)//count middle facets to divide them into two arrays
			{
				position0 = getLocOfPointRelativelyToPlane(figureMiddle[i].vertex[0]);
				position1 = getLocOfPointRelativelyToPlane(figureMiddle[i].vertex[1]);
				position2 = getLocOfPointRelativelyToPlane(figureMiddle[i].vertex[2]);

				if ((position0 > 0) || (position1 > 0) || (position2 > 0))
				{
					fli++;
				}
				else if ((position0 < 0) || (position1 < 0) || (position2 < 0))
				{
					fri++;
				}
			}


			Facet* midLeft = new Facet[fli]; //allocate arrays for left and right facets
			Facet* midRight = new Facet[fri];
			fri = 0;
			fli = 0;
			
			for (int i = 0; i < ((numOfFacets - right - left) * 3); i++)//divide them into two arrays
			{
				position0 = getLocOfPointRelativelyToPlane(figureMiddle[i].vertex[0]);
				position1 = getLocOfPointRelativelyToPlane(figureMiddle[i].vertex[1]);
				position2 = getLocOfPointRelativelyToPlane(figureMiddle[i].vertex[2]);

				if ((position0 > 0) || (position1 > 0) || (position2 > 0))
				{
					midLeft[fli].vertex[0] = figureMiddle[i].vertex[0];
					midLeft[fli].vertex[1] = figureMiddle[i].vertex[1];
					midLeft[fli].vertex[2] = figureMiddle[i].vertex[2];
					midLeft[fli].normal = figureMiddle[i].normal;
					fli++;
				}
				else if ((position0 < 0) || (position1 < 0) || (position2 < 0))
				{
					midRight[fri].vertex[0] = figureMiddle[i].vertex[0];
					midRight[fri].vertex[1] = figureMiddle[i].vertex[1];
					midRight[fri].vertex[2] = figureMiddle[i].vertex[2];
					midRight[fri].normal = figureMiddle[i].normal;
					fri++;
				}
			}

			this->writeFigure(figureRight, file_part2, right, this->comment, true, false);
			this->writeFigure(midRight, file_part2, fri, this->comment, false, false);
			this->writeFigure(planeMiddle, file_part2, numOfTriangelsInPlane, this->comment, false, true);



			for (int i = 0; i < numOfTriangelsInPlane; i++)//manipulations with a plane)
			{
				swap(planeMiddle[i].vertex[0].x, planeMiddle[i].vertex[1].x);
				swap(planeMiddle[i].vertex[0].y, planeMiddle[i].vertex[1].y);
				swap(planeMiddle[i].vertex[0].z, planeMiddle[i].vertex[1].z);
				
			}
			this->writeFigure(figureLeft, file_part1, left, this->comment, true, false);//write
			this->writeFigure(midLeft, file_part1, fli, this->comment, false, false);
			this->writeFigure(planeMiddle, file_part1, numOfTriangelsInPlane, this->comment, false, true);
			break;
		}
		else if (chooser == "2")///////////////////if in one file
		{
			for (int i = 0; i < left; i++)//left
			{
				figureLeft[i].vertex[0].z += distance;
				figureLeft[i].vertex[1].z += distance;
				figureLeft[i].vertex[2].z += distance;
			}
			for (int i = 0; i < right; i++)//right
			{
				figureRight[i].vertex[0].z -= distance;
				figureRight[i].vertex[1].z -= distance;
				figureRight[i].vertex[2].z -= distance;
			}
			for (int i = 0; i < ((numOfFacets - right - left) * 3); i++) //move crossed triangels a distance
			{
				position0 = getLocOfPointRelativelyToPlane(figureMiddle[i].vertex[0]);
				position1 = getLocOfPointRelativelyToPlane(figureMiddle[i].vertex[1]);
				position2 = getLocOfPointRelativelyToPlane(figureMiddle[i].vertex[2]);
				if (position0 < 0 || position1 < 0 || position2 < 0)
				{
					figureMiddle[i].vertex[0].z -= distance;
					figureMiddle[i].vertex[1].z -= distance;
					figureMiddle[i].vertex[2].z -= distance;
				}
				else
				{
					figureMiddle[i].vertex[0].z += distance;
					figureMiddle[i].vertex[1].z += distance;
					figureMiddle[i].vertex[2].z += distance;
				}
			}
			for (int i = 0; i < numOfTriangelsInPlane; i++)//move facets of plane a distance
			{
				planeMiddle[i].vertex[0].z += distance;
				planeMiddle[i].vertex[1].z += distance;
				planeMiddle[i].vertex[2].z += distance;
			}
			for (int i = 0; i < numOfTriangelsInPlane; i++)//manipulations with a plane)
			{
				swap(planeMiddle[i].vertex[0].x, planeMiddle[i].vertex[1].x);
				swap(planeMiddle[i].vertex[0].y, planeMiddle[i].vertex[1].y);
				swap(planeMiddle[i].vertex[0].z, planeMiddle[i].vertex[1].z);

			}


			this->writeFigure(figureLeft, file_solid, left, this->comment, true, false);//write
			this->writeFigure(figureRight, file_solid, right, this->comment, false, false);
			this->writeFigure(figureMiddle, file_solid, ((numOfFacets - right - left) * 3), this->comment, false, false);
			this->writeFigure(planeMiddle, file_solid, numOfTriangelsInPlane, this->comment, false, false);

			for (int i = 0; i < numOfTriangelsInPlane; i++)//move facets of plane a distance
			{
				planeMiddle[i].vertex[0].z -= 2*distance;
				planeMiddle[i].vertex[1].z -= 2*distance;
				planeMiddle[i].vertex[2].z -= 2*distance;
				swap(planeMiddle[i].vertex[0].x, planeMiddle[i].vertex[1].x);
				swap(planeMiddle[i].vertex[0].y, planeMiddle[i].vertex[1].y);
				swap(planeMiddle[i].vertex[0].z, planeMiddle[i].vertex[1].z);
			}
			this->writeFigure(planeMiddle, file_solid, numOfTriangelsInPlane, this->comment, false, true);
			break;
		}
		else
		{
			cout << "\nError value, try again:"; continue;
		}
	}
}