/*
http://programmingpraxis.com/2012/12/11/stepwise-program-development-a-heuristic-algorithm/

Stepwise Program Development: A Heuristic Algorithm
December 11, 2012
I recently found a book by Niklaus Wirth in a used book store; it’s a fascinating book and has been the source of a few recent exercises:

Niklaus Wirth, Eidgenössische Technische Hochschule, Zürich, Switzerland. Systematic Programming: An Introduction. 1973: Prentice-Hall, 
Inc. Englewood Cliffs, New Jersey. ISBN 0-13-880369-2.

Most of the book is concerned with teaching the syntax and semantics of Wirth’s language Pascal, but the final chapter is devoted to 
stepwise program development, where Wirth demonstrates by example four different problems which he solves by developing programs through 
a succession of stepwise refinements. The last section is a kind of “final exam” for readers; it’s the longest section of the book, by far, 
and gives a complete, detailed exposition of the solution to the following problem:

Generate a sequence of N characters, chosen from an alphabet of three elements (e.g., 1, 2, 3), such that no two immediately adjacent 
subsequences are equal.

For instance, the sequence of length N = 5 with the characters “12321″ is acceptable, but neither “12323″ nor “12123″ are.
*/

#include <iostream>
#include <vector>

static const unsigned int sc_maxVal = 3;
typedef unsigned int Val;
typedef std::vector<Val> Sequence;

class SuffixTreeNode;
typedef std::auto_ptr<SuffixTreeNode> SuffixTreeNodePtr;

/**
 * Class to keep the suffix tree node. 
 * Each node can have up to 3 (sc_maxVal) children.
 * E.g
 *                          o
 *          {1}            {2}           {3}
 *    {3,1} {3,2} {3,3}       {3,2}   {1,3} {3,3}
 *
 */
class SuffixTreeNode {
public:
	SuffixTreeNode() {
		children.resize(sc_maxVal);
	}

	Sequence fullValue_;						// Full subsequence, like {1,2}
	std::vector<SuffixTreeNodePtr> children_;	// Children
	std::vector<unsigned int> positions_;		// Positions where this subsequence already presents in the sequence
};

/*
void test() {
	Val expected[] = {
		1,
		2,
		3,

		1,2,
		1,3,
		2,1,
		2,3,
		3,1,
		3,2,

		1,2,1,
		1,2,3,
		1,3,1,
		1,3,2,
		2,1,2
		2,1,3



	};
}
*/

int main() {
	std::cout << "Hello World!" << std::endl;
	return 0;
}

