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
#include <deque>

static const unsigned int sc_maxVal = 3;
typedef unsigned int Val;
typedef std::deque<Val> Sequence;
typedef unsigned int uint;

bool hasRepeatingWithLen(const Sequence& sequence, uint len) {
	for (uint pos = 0; pos < len; ++pos) {
		if (sequence[pos] != sequence[pos + len]) {
			return false;
		}
	}
	return true;
}

// checks if there are any adjucent subsequences in the beginning of sequence.
// e.g. 1,2,1,2 or 1,1,3,2 will return true
//      1,2,3,3 or 1,3,1,2 will return false
bool noAdjucentSubsequencesInTheBeginning(const Sequence& sequence) {

	const uint halfSize = sequence.size()/2;
	for (uint i = 1; i <= halfSize; ++i) {
		if (hasRepeatingWithLen(sequence, i)) {
			return false;
		}
	}
	return true;
}

void buildSequence(const Sequence& sequence, uint maxSize) {

	for (Val val = 1; val <= sc_maxVal; ++val) {
		Sequence seq = sequence;
		seq.push_front(val);
		if (!noAdjucentSubsequencesInTheBeginning(seq)) {
			// there are adjucent equal subsequences, this is not a solution.
			continue;
		}

		// print out solution
		for (uint i = 0; i < seq.size(); ++i) {
			if (i) {
				std::cout << ", ";
			}
			std::cout << seq[i];
		}
		std::cout << std::endl;

		// Check longer sequences
		if (seq.size() < maxSize) {
			buildSequence(seq, maxSize);
		}
	}
}

int main() {
	Sequence sequence;
	buildSequence(sequence, 8);
	char c;
	std::cin >> c;
	return 0;
}

