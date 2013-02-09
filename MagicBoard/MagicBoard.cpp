#include <stdio.h>
#include <vector>
#include <set>
#include <memory>

typedef char Value;

struct Node {
   int parent_;
   int left_;
   int right_;
   Value value_;
   int leftCount_;
   int rightCount_;

   Node()
      : parent_(-1)
      , left_(-1)
      , right_(-1)
      , value_(0)
      , leftCount_(0)
      , rightCount_(0)
   {}

};

class DistanceTree {
public:
   // O(size) time
   DistanceTree(int size) {
      nodes_.resize(size);
      root_ = init(-1, 0, size - 1);
   }

   // O(Ln(size))
   void Set(int pos, Value val) {
      Node& node = nodes_[pos];

      const Value oldVal = node.value_;
      if (oldVal == val) {
         // Value is already there
         return;
      }

      // Set new value
      node.value_ = val;

      // Update parents up to the root
      int i = pos;
      while (i != root_) {
         const int parent = nodes_[i].parent_;
         int& valToUpdate = nodes_[parent].left_ == i ? 
            nodes_[parent].leftCount_ : nodes_[parent].rightCount_;
         valToUpdate += (val - oldVal);
         i = parent;
      }
   }

   // O(Ln(size))
   int CountFrom(int pos) {
      int result = 0;
      int i = pos;
      int iOld = nodes_[i].left_;

      while (i != -1) {
         if (nodes_[i].left_ == iOld) { // if we came from the left subtree (or this is the initial node)
            result += nodes_[i].value_ + nodes_[i].rightCount_;
         }
         iOld = i;
         i = nodes_[i].parent_;
      }

      return result;
   }

private:

   // Initializes subtree from nodes begin to end.
   // Returns subtree root node id.
   // parent is parent node.
   int init(int parent, int begin, int end) {
      const int middle = (end + begin) / 2;
      Node& root = nodes_[middle];
      root.parent_ = parent;
      root.leftCount_ = 0;
      root.rightCount_ = 0;

      if (middle - begin > 0) {
         root.left_ = init(middle, begin, middle - 1);
      }

      if (end - middle > 0) {
         root.right_ = init(middle, middle + 1, end);
      }

      return middle;
   }

   int root_;
   std::vector<Node> nodes_;
};

typedef std::auto_ptr<DistanceTree> DistanceTreePtr;

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

struct Operation {
    bool isWrite_; // type of operation
    bool isCol_;
    int colrow_;
    char value_;
    Operation(bool isCol, int colrow, char value, bool isWrite)
        : isCol_(isCol)
        , colrow_(colrow)
        , value_(value)
        , isWrite_(isWrite)
    {}
};
std::vector<Operation> operations;


int main() {
    int Q; // # of operations

    //std::cin >> N >> Q;
    scanf("%d %d\n", &N, &Q);

    int writesCount = 0; // number of write operation

    // Read operations
    char operation[100] = {0};
    while (Q--) {
        scanf("%s", &operation);
        //std::cin >> operation;
        int op = *((int*)operation);
        switch(op) {
            case rowSetOp:
            case colSetOp: {
                int colrow = 0;
                int value = 0;
                scanf(" %d %d\n", &colrow, &value);
                //std::cin >> colrow >> value;
                // colrow - 1 because it's 1-based
                operations.push_back(Operation(op == colSetOp, colrow - 1, static_cast<char>(value), true));
                ++writesCount;
                break;
            }
            case rowQueryOp:
            case colQueryOp: {
                int colrow = 0;
                //std::cin >> colrow;
                scanf(" %d\n", &colrow);
                // colrow - 1 because it's 1-based
                operations.push_back(Operation(op == colQueryOp, colrow - 1, 0, false));
            }
            default: {
                break;
            }
        }
    }
    // Data read ends
    ///////////////////////////////////////////////

    ///////////////////////////////////////////////
    // Proceeding data
    horOnes = DistanceTreePtr(new DistanceTree(writesCount));
    horZeros = DistanceTreePtr(new DistanceTree(writesCount));
    vertOnes = DistanceTreePtr(new DistanceTree(writesCount));
    vertZeros = DistanceTreePtr(new DistanceTree(writesCount));

    rows.resize(N);
    columns.resize(N);

    int step = 0;

    for (unsigned int i = 0; i < operations.size(); ++i) {
        Operation& oper = operations[i];
        if (oper.isWrite_) {
            // Writting
            //

            int pos = oper.colrow_;
            int value = oper.value_;
            RowCol& rowcol = oper.isCol_ ? columns[pos] : rows[pos];
            DistanceTree& ones = oper.isCol_ ? *horOnes : *vertOnes;
            DistanceTree& zeros = oper.isCol_ ? *horZeros : *vertZeros;

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
            ++step;
        } else {
            // Calculating
            //

            int pos = oper.colrow_;
            int val = 0;

            RowCol& rowcol = oper.isCol_ ? columns[pos] : rows[pos];
            if (rowcol.value_) {
                DistanceTree& zeros = oper.isCol_ ? *vertZeros : *horZeros;
                // how many zeros do we have after filling this row/col with ones for the last time
                val = zeros.CountFrom(rowcol.step_); 
            } else {
                DistanceTree& ones = oper.isCol_ ? *vertOnes : *horOnes;
                // how many ones do we have after filling this row/col with ones for the last time
                val = ones.CountFrom(rowcol.step_);
                val = N - val; // number of zeros
            }

            //std::cout << val << std::endl;
            printf("%d\n", val);
        }
    }
}
