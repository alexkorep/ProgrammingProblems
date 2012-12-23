/*
http://programmingpraxis.com/2012/11/27/amazon-interview-question/
Given a million points (x, y), give an O(n) solution to find the 100 points closest to (0, 0).

Alexey: we are looking for O(N) solution.
*/

#include "stdlib.h"
#include <vector>
#include <iostream>

// Intermedate structore used to find the points closest to (0,0)
// List of such structures will be (partially) sorted by distance member
struct Point {
	// Default ctor
	Point() : x(0), y(0), distance(0) {}
	
	// Ctor with non-default initialization
	Point(int x1, int y1)
		: x(x1)
		, y(y1)
		, distance(x*x + y*y) // Let's assume this is Euclidean space

	{}
	
	int x; // x-coordinate
	int y; // y-coordinate
	int distance; // Square of distance to (0,0);
};

typedef std::vector<Point> PointList;
static const int sc_pointCount = 10000000;
static const int maxCoordinate = 10000;
static const int sc_numPointsToFind = 100;

// Sorts point out to have the values bigger than |value| to be in the right, 
// smaller or equal - to be in the left.
// |startPos| and |endPos| - range to sort
// |value| element must present in the list.
// Returns the position of the last element smaller or equal to the value.
int SortOut(PointList& points, int value, int startPos, int endPos) {
	int i = startPos;
	int j = endPos;
	while (i < j) {
		while (points[i].distance <= value) ++i; // Find element > value
		while (points[j].distance > value) --j; // Find element <= value
		if (i < j) {
			std::swap(points[i], points[j]);
			++i;
			--j;
		}
	}
	return j;
}


// Finlds numPoints elements closest to zero and rearranges them to the 
// beginning of |points|
void findClosestPoints(PointList& points, int numPoints) {
	int startPos = 0;
	int endPos = points.size() - 1;
	
	// Value to use for sorting, all smaller values go to left, all
	// bigger ones go to right
	int value = points[0].distance; 
	while(startPos != numPoints) {
		const int pos = SortOut(points, value, startPos, endPos);
		std::cout << "( " << startPos << " - " << endPos << " )" << std::endl;
		
		if (pos > numPoints) {
			endPos = pos - 1;
			value = points[endPos].distance;
		} else if (pos < numPoints) {
			startPos = pos + 1;
			value = points[startPos].distance;
		} else { // pos == numPoints
			return;
		}
	}
}

int main()
{
	PointList points;

	// Generate points
	points.resize(sc_pointCount);
	for (unsigned int i = 0; i < points.size(); ++i) {
		points[i] = Point(
			rand()%(maxCoordinate*2) - maxCoordinate,
			rand()%(maxCoordinate*2) - maxCoordinate);
	}

	findClosestPoints(points, sc_numPointsToFind);

	// Print out results
	for (unsigned int i = 0; i < sc_numPointsToFind; ++i) {
		Point& point = points[i];
		std::cout << "(" << point.x << "," << point.y << ") ";
	}

	return 0;
}
