/*

Facebook Programming Challenge
Back to Question List Time Remaining: 01:42:32
Question 1 / 1

Mastermind is a game of two players. In the beginning, first player decides a secret key, which is a sequence (s1,s2,...sk) where 0 < si <= n, Then second player makes guesses in rounds, where each guess is of form (g1,g2, ...gk), and after each guess first player calculates the score for the guess. Score for a guess is equal to number of i's for which we have gi = si.

For example if the secret key is (4,2,5,3,1) and the guess is (1,2,3,7,1),then the score is 2, because
g2 = s2 and g5 = s5. 

Given a sequence of guesses, and scores for each guess, your program must decide if there exists at least one secret key that generates those exact scores.

Input

First line of input contains a single integer C (1 <=C <= 100). C test-cases follow. First line of each test-case contains three integers n,k and q. (1 <=n,k <=11, 1<=q<=8 ). Next q lines contain the guesses.

Each guess consists of k integers gi,1, gi,2,....gi,k separated by a single space, followed by the score for the guess bi (1 <= gi,j <=n for all 1 <=i <=q, 1 <=j <=k; and 0 <= bi <=k )

Output

For each test-case, output "Yes" (without quotes), if there exists at least a secret key which generates those exact scores, otherwise output "No".

Sample Input
2

4 4 2
2 1 2 2 0
2 2 1 1 1
4 4 2
1 2 3 4 4
4 3 2 1 1

Sample Output

Yes 
No

*/

#include <iostream>
#include <vector>

typedef unsigned int uint;

uint maxVal = 0;
uint numNumbers = 0;
uint numGuesses = 0;
std::vector<std::vector<uint> > guesses;
std::vector<uint> results;

std::vector<bool> outputs;

bool checkTail(uint offset, const std::vector<uint>& adjustedResults) {
	std::vector<uint> adjustedResults2;
	for (uint i = 0; i <= maxVal; ++i) {

		adjustedResults2 = adjustedResults;

		bool allResulstAreZero = true;
		for (uint j = 0; j < numGuesses; ++j) {
			uint& resultForThisGuess = adjustedResults2[j];
			if (guesses[j][offset] == i) {
				if (resultForThisGuess == 0) {
					// we don't have any matching numbers for this guess so we cannot proceed
					return false;
				}
				--resultForThisGuess;
			}
			if (resultForThisGuess != 0) {
				allResulstAreZero = false;
			}
		}
		if (offset == numNumbers - 1) {
			// We went till the end number. Now need to check if we have all resilt zero end exit.
			return allResulstAreZero;
		}

		if (checkTail(offset + 1, adjustedResults2)) {
			return true;
		}
	}

	return false;
}

void checkSolutions() {
	std::cin >> maxVal;
	std::cin >> numNumbers;
	std::cin >> numGuesses;

	guesses.resize(numGuesses);
	results.resize(numGuesses);
	for (uint i = 0; i < numGuesses; ++i) {
		guesses[i].resize(numNumbers);
		for (uint j = 0; j < numNumbers; ++j) {
			std::cin >> guesses[i][j];
		}
		std::cin >> results[i];
	}

	outputs.push_back(checkTail(0, results));
}


int main() {
	uint numTests = 0;
	std::cin >> numTests;
	for (uint i = 0; i < numTests; ++i) {
		checkSolutions();
	}


	for (uint i = 0; i < numTests; ++i) {
		std::cout << (outputs[i] ? "yes" : "no") << std::endl;
	}

	// Just wait for input
	std::cin >> numTests;
	return 0;
}

