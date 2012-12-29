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

#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Answers
vector<int> a;
vector<int> b;

// |i| is inside this |solutions| set when |i| equals to the number of knights which said there are i knights (knights[i] == i)
set<int> solutions;

vector<int> diff;

void solveCase(istream& istr, ostream& ostr) {
   int numPeople = 0;
   istr >> numPeople;

   // Read solutions from stream
   a.resize(numPeople);
   b.resize(numPeople);
   for (int i = 0; i < numPeople; ++i) {
      istr >> a[i] >> b[i];
   }

   // Build diff array
   diff.resize(numPeople + 2);
   std::fill(diff.begin(), diff.end(), 0);
   for (int i = 0; i < numPeople; ++i) {
      ++diff[a[i]];
      --diff[b[i] + 1];
   }

   // Find solutions
   solutions.clear();
   int val = 0;
   for (int i = 0; i <= numPeople; ++i) {
      val += diff[i];
      if (val == i) {
         solutions.insert(i);
      }
   }

   ostr << solutions.size() << endl;

   // Find the first solution lexicographically
   int min = solutions.empty() ? 0 : *solutions.begin();
   int max = solutions.empty() ? 0 : *solutions.rbegin();
   for (int i = 0; i < numPeople; ++i) {
      if (solutions.empty()) {
         ostr << "0";
         continue;
      }

      if (a[i] <= min && max <= b[i]) {
         // All possible solution are within the answer this bytelandian gave
         ostr << "1";
      } else {
         solutions.erase(solutions.lower_bound(a[i]), solutions.upper_bound(b[i]));
         min = *solutions.begin();
         max = *solutions.rbegin();
         ostr << "0";
      }
   }
   ostr << endl;
}

void Solve(istream& istr, ostream& ostr) {
   int casesCount = 0;
   istr >> casesCount;
   for (int i = 0; i < casesCount; ++i) {
      solveCase(istr, ostr);
   }
}

int main()
{
   /*
   string test01 = 
      "3\n"

      "1\n"
      "0 1\n"

      "4\n"
      "1 4\n"
      "2 4\n"
      "3 4\n"
      "4 4\n"

      "3\n"
      "1 2\n"
      "0 0\n"
      "1 3\n";
   */
   /*
   1
   1
   5
   0000
   1
   101
   */

   /*
   string expected01 = 
      "1\n1";

   stringstream result;
   Solve(stringstream(test01), result);
   expected01 = result.str();
   */
   Solve(cin, cout);
   return 0;
}