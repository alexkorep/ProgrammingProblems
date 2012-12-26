/*
It's the 1st of the month again, which means it's time for Dave to pay his bills. Dave needs to go to 
the post office to mail his rent cheque, and wants to take the shortest route possible. Dave wonders 
how many different shortest routes he can take.

Dave lives at the southwest corner of town (0,0) and the post office is at the northeast corner of town (W,H). 
It takes Dave exactly one minute to move from (x, y) to (x, y+1), (x, y-1), (x+1, y) or (x-1, y). 
Dave cannot move further south or west than his house, nor can he move further north or east than the 
post office (that is, Dave's x coordinate must stay between 0 and W, and his y coordinate must stay 
between 0 and H at all times). Additionally, there are N intersections that are being worked on by 
construction crews, and Dave must avoid these intersections.

The number of shortest routes may be very large, so print the result modulo 1000000037. If it is impossible 
for Dave to reach the post office, the answer is 0.

Input:

Input begins with an integer T, the number of test cases. Each test case begins with 3 integers W, H, N. 
N lines follow, each containing 2 integers (xi, yi), the coordinates of an intersection being worked on 
by a construction crew. Intersections are guaranteed to be unique, and neither (0,0) nor (W,H) will be 
under construction. A blank line separates each test case.

Output:

For each test case, output a line containing the number of shortest paths to the post office, modulo 1000000037.
Sample input:

3

2 2 1
1 1

1 1 2
0 1
1 0

7 1 2
1 0
4 1
Sample output:

2
0
6
Constraints

1<=T<=30
1<=W,H<=107
0<=xi<=W
0<=yi<=H
0<=N<=max(100,min(W,H,1000))
*/

#include <iostream>
#include <vector>
#include <bitset>
#include <limits>

using namespace std;

typedef vector<vector<bool> > Blocks;
vector<int> solutions;

static const int modulo = 1000000037;
typedef unsigned long long uint;

void increment(int& nSolution) {
	++nSolution;
	if (nSolution >= modulo) {
		nSolution = 0;
	}
}

// |nSolution| number of solutions
// |nLength| current solution length
// |nMinSolutionLength| - minimal length of solutions
void travelse(int x, int y, 
			  int w, int h,
			  Blocks& visited,
			  int& nSolution, 
			  uint nLength,
			  uint& nMinSolutionLength) {

	if (nLength > nMinSolutionLength) {
		// Don't consider solutions longer than the shortest one
		return;
	}

	if (x == w && y == h) {
		if (nMinSolutionLength == nLength) {
			increment(nSolution);
		} else {
			nMinSolutionLength = nLength;
			nSolution = 1;
		}

		return;
	}

	Blocks visited1;
	visited[y][x] = true;

	if (x < w && !visited[y][x + 1]) {
		visited1 = visited;
		travelse(x + 1, y, w, h, visited1, nSolution, nLength + 1, nMinSolutionLength);
	}

	if (x > 0 && !visited[y][x - 1]) {
		visited1 = visited;
		travelse(x - 1, y, w, h, visited1, nSolution, nLength + 1, nMinSolutionLength);
	}

	if (y < h && !visited[y + 1][x]) {
		visited1 = visited;
		travelse(x, y + 1, w, h, visited1, nSolution, nLength + 1, nMinSolutionLength);
	}

	if (y > 0 && !visited[y - 1][x]) {
		visited1 = visited;
		travelse(x, y - 1, w, h, visited1, nSolution, nLength + 1, nMinSolutionLength);
	}
}

void solve() {
	int w = 0;
	int h = 0;
	int nBlocks = 0;
	cin >> w >> h >> nBlocks;
	Blocks blocks;
	blocks.resize(h + 1);
	for (int y = 0; y <= h; ++y) {
		blocks[y].resize(w + 1);
	}

	for (int i = 0; i < nBlocks; ++i) {
		int x = 0;
		int y = 0;
		cin >> x >> y;
		blocks[y][x] = true;
	}

	int nSolution = 0;
	uint nMinSolutionLength =  numeric_limits<unsigned long long>::max();
	travelse(0, 0, w, h, blocks, nSolution, 1, nMinSolutionLength);
	solutions.push_back(nSolution);
}

int main()
{
	int nCases = 0;
	cin >> nCases;
	for (int i = 0; i < nCases; ++i) {
		solve();
	}

	for (unsigned int i = 0; i < solutions.size(); ++i) {
		cout << solutions[i] << endl;
	}

	return 0;
}