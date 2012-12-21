/*

This problem is based on slightly modified problems from
http://programmingpraxis.com/2012/11/16/list-intersection-and-union/
http://programmingpraxis.com/2012/11/20/list-difference/

You are given two linked lists of integers with no duplicates. 

1. The intersection of the two lists is a list of integers that are in both lists.
2. The union of the two lists is a list of integers that are in either list.
3. The difference is the items in the first list that are not in the second list. 

For instance, if list A contains the integers 4, 7, 12, 6, 17, 5 and 13 and list B contains the integers 7, 19, 4, 11, 13, 2, and 15 their 
intersection is the list 4, 7, and 13 and their union is the list 4, 7, 12, 6, 17, 5, 13, 19, 11, 2 and 15.

For our sample lists A containing 4, 7, 12, 6, 17, 5, and 13 and B containing 7, 19, 4, 11, 13, 2, and 15, 
the difference A − B is 12, 6, 17, and 5 and the difference B − A is 19, 11, 2, and 15.

Your task is to write the list differencing function and the functions that perform intersection and union with time complexity of O(n).
*/

#include <list>
#include <unordered_set>
#include <iterator>

template <class T>
void operations(const std::list<T>& list1, const std::list<T>& list2,
	std::list<T>& intersection,
	std::list<T>& theUnion,
	std::list<T>& aMinusB,
	std::list<T>& bMinusA) 
{
	typedef std::unordered_set<T> Hashtable;
	Hashtable set1;
	Hashtable set2;
	std::copy(list1.begin(), list1.end(), std::inserter(set1, set1.end()));
	std::copy(list2.begin(), list2.end(), std::inserter(set2, set2.end()));

	for (Hashtable::const_iterator i = set1.begin(); i != set1.end(); ++i) {
		if (set2.find(*i) != set2.end()) {
			// *i found in both sets
			intersection.push_back(*i);
		} else {
			// *i is located in set1 only.
			aMinusB.push_back(*i);
			theUnion.push_back(*i);
		}
	}

	for (Hashtable::const_iterator i = set2.begin(); i != set2.end(); ++i) {
		if (set1.find(*i) == set1.end()) {
			// *i found in set2 only
			bMinusA.push_back(*i);
		}
		theUnion.push_back(*i);
	}

}

int main()
{
	const int A[] = {4, 7, 12, 6, 17, 5, 13};
	const int B[] = {7, 19, 4, 11, 13, 2, 15};

	std::list<int> intersection;
	std::list<int> theUnion;
	std::list<int> aMinusB;
	std::list<int> bMinusA;

	operations(
		std::list<int>(A, A + sizeof(A)/sizeof(A[0])),
		std::list<int>(B, B + sizeof(B)/sizeof(B[0])),
		intersection, theUnion, aMinusB, bMinusA);

	return 0;
}

