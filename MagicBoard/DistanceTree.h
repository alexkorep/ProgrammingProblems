#include <vector>
#include "assert.h"

#pragma once

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