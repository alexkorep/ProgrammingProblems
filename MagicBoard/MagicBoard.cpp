
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
