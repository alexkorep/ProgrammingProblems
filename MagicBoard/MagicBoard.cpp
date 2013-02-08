/*
Long long ago, there is a magic board. The magic board has N*N cells: N rows and N columns. Every cell contains one integer, which is 0 initially. Let the rows and the columns be numbered from 1 to N.
There are 2 types of operations can be applied to the magic board:
RowSet i x: it means that all integers in the cells on row i have been changed to x after this operation.
ColSet i x: it means that all integers in the cells on column i have been changed to x after this operation.
And your girlfriend sometimes has an interest in the total number of the integers 0s on some row or column.
RowQuery i: it means that you should answer the total number of 0s on row i.
ColQuery i: it means that you should answer the total number of 0s on column i.
Input

The first line of input contains 2 space-separated integers N and Q. They indicate the size of the magic board, and the total number of operations and queries from the girlfriend.
Then each of the next Q lines contains an operation or a query by the format mentioned above.
Output

For each query, output the answer of the query.
Constraints

1 ? N, Q ? 500000 (5 * 105)
1 ? i ? N
x ? {0, 1} (That is, x = 0 or 1)
Sample

Input:
3 6
RowQuery 1
ColSet 1 1
RowQuery 1
ColQuery 1
RowSet 1 0
ColQuery 1

Output:
3
2
0
1
Explanation

At first, the magic board is
000 <- row 1
000
000
So the answer of first query "RowQuery 1" is 3.
After the "ColSet 1 1", the board becomes
column 1
|
V
100
100
100
So the answer of the second query "RowQuery 1" is clearly 2, since the cell (1,1) became 1. And the answer of the third query "ColQuery 1" is 0.
Finally, apply the operation "RowSet 1 0", the board has changed to
000
100
100
From this board, the answer of the last query "ColQuery 1" should be 1.
*/

#include <stdio.h>
#include <vector>
#include <iostream>
#include <set>
#include <memory>
#include "DistanceTree.h"

const int rowSetOp = 'SwoR'; //'RowS';
const int colSetOp = 'SloC'; //'ColS';
const int rowQueryOp = 'QwoR'; //'RowQ';
const int colQueryOp = 'QloC'; //'ColQ';

struct RowCol {
    Value value_; // Which value was written in this row/column last time (could be 0 or 1)
    int step_;    // Step # when this value was written

    // Constructor
    RowCol()
        : value_(0)
        , step_(0)
    {}
};

int N; // size

typedef std::vector<RowCol> RowColVector;

RowColVector rows;
RowColVector columns;

// Keeps steps which filled horizontal lines consisting of ones. If there are 2 steps filling 
// the same row, the last one overwrites the first one (old one removed from the set, new one is added).
// If the line with 0's overwrites the old line, the old line step # removed from the set.
DistanceTreePtr horOnes;

// Step ## which fill horizontal lines with zeros
DistanceTreePtr horZeros;

// Step ## which fill vertical lines with ones
DistanceTreePtr vertOnes;

// Step ## which fill horizontal lines with ones
DistanceTreePtr vertZeros;

int main() {
    int Q; // # of operations
    std::cin >> N >> Q;

    horOnes = DistanceTreePtr(new DistanceTree(Q));
    horZeros = DistanceTreePtr(new DistanceTree(Q));
    vertOnes = DistanceTreePtr(new DistanceTree(Q));
    vertZeros = DistanceTreePtr(new DistanceTree(Q));

    rows.resize(N);
    columns.resize(N);

    // Read operations
    char operation[100] = {0};
    int step = 0;
    while (step < Q) {
        std::cin >> operation;
        int op = *((int*)operation);
        switch(op) {
            case rowSetOp:
            case colSetOp: {
                int pos = 0;
                int value = 0;
                std::cin >> pos >> value;
                RowCol& rowcol = (op == colSetOp) ? columns[pos] : rows[pos];
                DistanceTree& ones = (op == colSetOp) ? *horOnes : *vertOnes;
                DistanceTree& zeros = (op == colSetOp) ? *horZeros : *vertZeros;

                if (rowcol.value_) {
                    // We overwrite 1
                    ones.Set(rowcol.step_, 0);
                } else {
                    // We overwrite 0
                    zeros.Set(rowcol.step_, 0);
                }

                if (value) {
                    // Setting new 1 value
                    ones.Set(step, 1);
                } else {
                    // Setting new 0 value
                    zeros.Set(step, 1);
                }
                rowcol.step_ = step;
                rowcol.value_ = value;

                break;
            }
            case rowQueryOp:
            case colQueryOp: {
                int pos = 0;
                std::cin >> pos;

                int val = 0;

                RowCol& rowcol = (op == colQueryOp) ? columns[pos] : rows[pos];
                if (rowcol.value_) {
                    DistanceTree& zeros = (op == colQueryOp) ? *horZeros : *vertZeros;
                    // how many zeros do we have after filling this row/col with ones for the last time
                    val = zeros.CountFrom(rowcol.step_); 
                } else {
                    DistanceTree& ones = (op == colQueryOp) ? *horOnes : *vertOnes;
                    // how many ones do we have after filling this row/col with ones for the last time
                    val = ones.CountFrom(rowcol.step_);
                    val = N - val; // number of zeros
                }

                std::cout << val;
            }
            default: {
                break;
            }
        }
        ++step;
    }
}
