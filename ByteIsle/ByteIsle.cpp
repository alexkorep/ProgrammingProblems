/*
A long school holiday has come, and you decided to visit the famous Byte Island. You know 
there are only two types of Bytelandians: Byteknights and Byteknaves. A Byteknight always 
tells the truth, whereas a Byteknave always lies.

It is known that there are N Bytelandians in the island, and now you meet all of them. You 
are curious about their types. Because you are a smart logician, you don't want to ask them 
questions that immediately reveal their types (that's too boring). Instead, to each Bytelandian 
you ask, "How many Byteknights are there here?"

To your surprise, they also don't answer your questions directly. Instead, the i-th Bytelandian 
answers of the form "The number of Byteknights here is between ai and bi, inclusive". You record 
all answers in your pocket note.

Now that you have collected all information you need, determine the type of each Bytelandian.
Input

The first line contains a single integer T, the number of test cases. T test cases follow. 
The first line of each test case contains a single integer N. N lines follow. The i-th 
line contains two integers ai and bi.
Output

For each test case, output two lines. In the first line, output a single integer indicating the 
number of different solutions, modulo 1000000007. In the next line, output the lexicographically 
smallest solution. A solution is a string consisting of N characters, where the i-th character 
of the string is '1' if the i-th Bytelandian is a Byteknight, or '0' in case of a Byteknave. 
It is guaranteed that there is at least one valid solution.
Example

Input:
3
1
0 1
4
1 4
2 4
3 4
4 4
3
1 2
0 0
1 3

Output:
1
1
5
0000
1
101
Constraints

1 <= T <= 5
1 <= N <= 50000
0 <= ai <= bi <= N
*/

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include "ByteIsle.h"

using namespace std;

typedef pair<int, int> Answer;
typedef vector<Answer> Answers;
typedef map<int, int> SolutionIntervals;
/*
typedef vector<int> Solution; // 1 = knight, 0 = knave

static const int modulo = 1000000037;

void increment(int& nSolution) {
	++nSolution;
	if (nSolution >= modulo) {
		nSolution = 0;
	}
}
*/

// reads answers and returns number of Bytelandians
int readAnswers(Answers& answers) {
	int nBytelandians = 0;
	cin >> nBytelandians;

	answers.resize(nBytelandians + 1);
	for (int i = 1; i <= nBytelandians; ++i) {
		cin >> answers[i].first >> answers[i].second;
	}
	return nBytelandians;
}

void printResult(int numberOfSolutions, const vector<bool>& fistSolution)
{
	cout << numberOfSolutions << endl;
	for (unsigned int i = 0; i < fistSolution.size(); ++i) {
		cout << (fistSolution[i] ? "1" : "0") << " ";
	}
	cout << endl;
}


void solve() {
	Answers answers; // 1-based vector of answers
	const int nBytelandians = readAnswers(answers);

	// knights[i] = number of people who told that there are i knights.
	// knightDiff[i] = knights[i] - knights[i - 1];

	// Build knightDiff
	vector<int> knightDiff(nBytelandians + 1, 0);
	for (int i = 0; i <= nBytelandians; ++i) {
		++knightDiff[answers[i].first];
		const int& answerMax = answers[i].second;
		if (answerMax < nBytelandians) {
			--knightDiff[answerMax + 1];
		}
	}

	// build knights
	int curKnights = 0;
	vector<int> knights(nBytelandians + 1, 0);
	for (int i = 0; i <= nBytelandians; ++i) {
		curKnights += knightDiff[i];
		knights[i] = curKnights;
	}

	// find solutions
	int numberOfSolutions = 0;
	vector<bool> solutions(nBytelandians + 1, false);
	for (int i = 0; i <= nBytelandians; ++i) {
		if (i == knights[i]) {
			++numberOfSolutions;
			solutions[i] = true;
		}
	}

	// Now we need to find the first lexographical solution
	// find solution intervals. Invervals are stored in map, [a, b] is stored in the way that map[a] = b.
	int intervalBegin = -1;
	IntervalRemover remover;
	for (int i = 0; i <= nBytelandians; ++i) {
		if (solutions[i] && intervalBegin < 0) {
			intervalBegin = i;
		} else if (!solutions[i] && intervalBegin >= 0) {
			remover.add(intervalBegin, i - 1);
			intervalBegin = -1;
		}
	}

	// Close the last interval
	if (intervalBegin >= 0) {
		remover.add(intervalBegin, nBytelandians);
	}


	// Go through all alswers and eliminate solutions which are inside of answer if number of solutions left will stay > 0
	vector<bool> fistSolution(nBytelandians, true);
	int numberOfSolutionsLeft = numberOfSolutions;
	for (int i = 1; i <= nBytelandians; ++i) {
		const int& a = answers[i].first;
		const int& b = answers[i].second;

		const int removed = remover.removeIntervals(a, b, numberOfSolutionsLeft - 1);
		numberOfSolutionsLeft -= removed;
		if (!removed) {
			fistSolution[i - 1] = false;
		}
	}

	printResult(numberOfSolutions, fistSolution);
}



int main()
{
	int nCases = 0;
	cin >> nCases;
	for (int i = 0; i < nCases; ++i) {
		solve();
	}

	/*
	const int N = 50000;
	cout << N << endl;
	for (int i = 0; i < N; ++i) {
		int a = rand()%N;
		int b = rand()%N;
		if (a > b) swap(a, b);
		cout << a << " " << b << endl;
	}
	*/

	return 0;
}

