#include <stdio.h>
#include <vector>
#include <iostream>
#include <set>

const int rowSetOp = 'SwoR'; //'RowS';
const int colSetOp = 'SloC'; //'ColS';
const int rowQueryOp = 'QwoR'; //'RowQ';
const int colQueryOp = 'QloC'; //'ColQ';

const int colMask = 0x10000;

struct Operation {
    bool isCol_;
    int colrow_;
    char value_;
    Operation(bool isCol, int colrow, char value)
        : isCol_(isCol)
        , colrow_(colrow)
        , value_(value) 
    {}
};

int N; // size

std::vector<Operation> operations;

int getColRowVal(bool isCol, int colrow) {
    std::set<int> onesCols; // rows/columns which were changed to 1
    std::set<int> zerosCols; // rows/columns which were changed to 0
    int val = N; // number of zeros
    for (unsigned int i = 0; i < operations.size(); ++i) {
        Operation& op = operations[i];
        if (isCol == op.isCol_) {
            val = op.value_ ? 0 : N;
            onesCols.clear();
            zerosCols.clear();
        } else {
            if (op.value_) {
                onesCols.insert(op.colrow_);
            } else {
                zerosCols.insert(op.colrow_);
            }
        }
    }

    if (val > 0) {
        val -= onesCols.size();
    } else {
        val = zerosCols.size();
    }

    return val;
}

int main() {
    int Q; // # of operations
    std::cin >> N >> Q;

    // Read operations
    char operation[100] = {0};
    while (Q--) {
        //scanf("%s", &operation);
        std::cin >> operation;
        int op = *((int*)operation);
        switch(op) {
            case rowSetOp:
            case colSetOp: {
                int colrow = 0;
                int value = 0;
                //scanf("%d, %d\n", &colrow, &value);
                std::cin >> colrow >> value;
                operations.push_back(Operation(op == colSetOp, colrow, static_cast<char>(value)));
                break;
            }
            case rowQueryOp:
            case colQueryOp: {
                int colrow = 0;
                //scanf("%d\n", &colrow);
                std::cin >> colrow;
                const int val = (op == colQueryOp) ? getColRowVal(true, colrow) : getColRowVal(false, colrow);
                //printf("%d\n", val);
                std::cout << val;
            }
            default: {
                break;
            }
        }
    }
}
