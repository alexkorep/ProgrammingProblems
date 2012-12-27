#ifndef __BITEISLE_H__
#define __BITEISLE_H__

#include <vector>
#include <map>

using namespace std;

class IntervalRemover {
	friend struct RemoverTester;
public:

	IntervalRemover() {}

	// Adds [a, b] inteval
	// No check for non-inetsection or validity is performed
	// O(log N) complexity
	void add(int a, int b) {
		begins[a] = b;
		ends[b] = a;
	}

	// Clears internal containers
	void clear() {
		begins.clear();
		ends.clear();
	}

	// Return end of the interval starting in |a|. If there is no such interval, returns -1
	int getInterval(int a) const {
		const std::map<int, int>::const_iterator i = begins.find(a);
		if (i == begins.end()) {
			return -1;
		}
		return i->second;
	}

	// return number of intervals left
	int size() const {
		return begins.size();
	}

	// Removes all points inside [a, b]. If intervals intersect
	// |a| or |b|, they are rebuilt
	// |maxPointsToRemove| - maximum number of points to remove. If total points being
	// removed exceeds this number, nothing will be removed at all.
	// Returns number of points being actually removed
	int removeIntervals(int a, int b, int maxPointsToRemove) {

		// Just exit if we are not allowed to remove anything.
		if (0 == maxPointsToRemove) {
			return 0;
		}

		const int leftPoint = findFirstIntervalToTheRight(a);
		const int rightPoint = findFistIntervalToTheLeft(b);
		if (leftPoint == -1 || rightPoint == -1 || leftPoint > rightPoint) {
			// No intervals found inside [a, b], just return
			return 0;
		}

		// find interators corresponding to the leftPoint and rightPoint 
		// in the |begins| and |ends| containers. Since these are valid points,
		// iterators we found are also valid.
		IntervalType::iterator beginsBegin = begins.find(leftPoint);
		IntervalType::iterator endsBegin = ends.find(beginsBegin->second);
		IntervalType::iterator endsEnd = ends.find(rightPoint); 
		IntervalType::iterator beginsEnd = begins.upper_bound(endsEnd->second); // to make it pointing *after* the last element
		++endsEnd; // to make it pointing *after* the last element

		// calculate number of points inside [a, b]
		int numberOfPoints = getNumberOfPoinst(beginsBegin, beginsEnd);
		// remove points outside of [a, b]
		if (leftPoint < a) {
			numberOfPoints -= (a - leftPoint);
		}
		if (rightPoint > b) {
			numberOfPoints -= (rightPoint - b);
		}

		// check if we are about to remove more points than |maxPointsToRemove|
		if (numberOfPoints > maxPointsToRemove) {
			return 0;
		}

		// Remove all found intevals
		begins.erase(beginsBegin, beginsEnd);
		ends.erase(endsBegin, endsEnd);

		// Restore the points that were in removed intervals but outside of [a, b]
		if (leftPoint < a) {
			begins[leftPoint] = a - 1;
			ends[a - 1] = leftPoint;
		}

		if (rightPoint > b) {
			begins[b + 1] = rightPoint;
			ends[rightPoint] = b + 1; 
		}

		return numberOfPoints;
	}

private:
	typedef std::map<int, int> IntervalType;

	// Finds first interval [a, b] such than b >= pos
	// Returns |a| or -1 if no interval found
	// O(logN)
	int findFirstIntervalToTheRight(int pos) const {
		// find [a, b] with b >= pos
		IntervalType::const_iterator right = ends.lower_bound(pos);
		if (right == ends.end()) {
			return -1;
		}
		return right->second;
	}
	
	// Finds last interval [a, b] such than a <= pos
	// Returns |b| or -1 if no interval found
	// O(logN)
	int findFistIntervalToTheLeft(int pos) const {
		if (ends.empty()) {
			return -1;
		}

		// find first [a, b] interval with a > pos
		IntervalType::const_iterator right = begins.upper_bound(pos);
		if (right == begins.begin()) {
			return -1;
		}
		// Get previous interval
		--right;
		return right->second;
	}

	// Calculates number of point insite 2 |begins| iterators
	// |begins1| and |begins2| - iterator to |begins| container
	// [begins1, begins2) elements used to calculate
	int getNumberOfPoinst(const IntervalType::const_iterator& begins1, 
	                      const IntervalType::const_iterator& begins2) const {
		int sum = 0;
		IntervalType::const_iterator i = begins1;
		for (; i != begins2; ++i) {
			sum += i->second - i->first + 1;
		}
		return sum;
	}

private:
	IntervalType begins; // list of [a, b] interfals in begins[a] = b format
	IntervalType ends;   // list of [a, b] interfals in ends[b] = a format
};

#endif // #ifndef __BITEISLE_H__