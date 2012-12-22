/*
http://programmingpraxis.com/2012/11/27/amazon-interview-question/
Given a million points (x, y), give an O(n) solution to find the 100 points closest to (0, 0).

Alexey: we are looking for O(N) solution.
*/

#include <vector>

// Intermedate structore used to find the points closest to (0,0)
// List of such structures will be (partially) sorted by distance member
struct Point {
	int x;
	int y;
	int distance; // Square of distance to (0,0);
};

typedef std::vector<Point> PointList;
static const int sc_pointCount = 10000000;
static const int maxCoordinate = 10000;

// Sorts point out to have the values bigger than value to be in the right, smaller - to be in the left.
// startPos and endPos - range to sort
// Returns the first position of the point bigger of equal to the value
int SortOut(PointList& points, int value, int startPos, int endPos) {
	int i = startPos;
	int j = endPos;
	while (i < j) {
		while (points[i].distance < value) ++i;
		while (points[j].distance > value) --j;
		if (i < j) {
			std::swap(points[i], points[j]);
		}
	}
	return i;
}

void findClosestPoints(PointList& points, int numPoints) {
	int startPos = 0;
	int endPos = points.size() - 1;
	while(startPos != numPoints) {
		const int value = points[startPos].distance;
		const int pos = SortOut(points, value, startPos, endPos);
		if (pos > numPoints) {
			endPos = pos;
		} else if (pos < numPoints) {
			startPos = pos;
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
		Point& point = points[i];
		point.x = rand()%(maxCoordinate*2) - maxCoordinate;
		point.y = rand()%(maxCoordinate*2) - maxCoordinate;
		// Let's assume this is Euclidean space
		point.distance = point.x*point.x + point.y*point.y;
	}

	findClosestPoints(points, 100);

	return 0;
}

