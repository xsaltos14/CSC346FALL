//
//  BSTChecker.h
//  csc326BTS
//
//  Created by xavier saltos on 11/16/25.
//

#ifndef BSTCHECKER_H
#define BSTCHECKER_H
#include "BSTNode.h"
#include <unordered_set>
#include <limits>

class BSTChecker {
public:

   // CheckBSTValidity:
   //   - Returns nullptr if the tree is a valid BST.
   //   - Returns the *first* node in preorder that violates rules.
   // Rules checked:
   //   1) Key-related problems:
   //        - Node's key outside the allowed range.
   //        - Duplicated key via location.
   //   2) Child-related problems:
   //        - A node pointer appears more than once (shared child).
   //        - A cycle.
   //NOTE: Preorder means:
   //       Check current node → check left subtree → check right subtree
   static BSTNode* CheckBSTValidity(BSTNode* rootNode) {

      // If tree is empty, it is automatically valid
      if (!rootNode) {
         return nullptr;
      }

      // Set of nodes already visited — helps detect shared/cycled nodes
      unordered_set<BSTNode*> visited;

      // Start with the widest possible range for integer keys.
      // long long used so we can safely subtract/ add 1.
      long long minKey = numeric_limits<long long>::min();
      long long maxKey = numeric_limits<long long>::max();

      // Call the recursive function to check the whole tree
      return CheckNode(rootNode, minKey, maxKey, visited);
   }

private:

   // Recursive helper: CheckNode
   //   node      → the current node being checked
   //   minKey    → minimum allowed key for this node
   //   maxKey    → maximum allowed key for this node
   //   visited   → set of previously visited node pointers
   //
   // Returns:
   //   - nullptr → if subtree is valid
   //   - pointer → to the FIRST violating node (in preorder)
   //
   // This function performs a strict BST check:
   //   left subtree keys must be strictly < parent key
   //   right subtree keys must be strictly > parent key
   static BSTNode* CheckNode(BSTNode* node,
                             long long minKey,
                             long long maxKey,
                             unordered_set<BSTNode*>& visited) {

      // Null node means we've reached an empty child — fine.
      if (!node) {
         return nullptr;
      }

      // CHILD-RELATED PROBLEM:
      // If we have already encountered this node pointer,
      // it means the structure is invalid due to sharing or cycles.
      if (visited.find(node) != visited.end()) {
         return node;  // return the first repeated node
      }

      // Mark this node as visited
      visited.insert(node);


      // KEY-RELATED PROBLEM:
      // Check if node's key violates the allowed min/max range.
      // If node->key is outside the allowed range, the BST rule
      // was already violated higher in the tree.
      // -----------------------------------------------
      if (node->key < minKey || node->key > maxKey) {
         return node;
      }


      // PREORDER CHECK:
      //  1) Check current node (done above)
      //  2) Check LEFT subtree

      // Left child must satisfy:
      //    minKey <= leftKey <= (node->key - 1)
      BSTNode* bad = CheckNode(node->left,
                               minKey,
                               static_cast<long long>(node->key) - 1,
                               visited);

      // If a bad node was found in the left subtree, return it
      if (bad) {
         return bad;
      }
      //  3) Check RIGHT subtree
      // Right child must satisfy:
      //   (node->key + 1) <= rightKey <= maxKey
      bad = CheckNode(node->right,
                      static_cast<long long>(node->key) + 1,
                      maxKey,
                      visited);

      // If right subtree has a violation, return it
      if (bad) {
         return bad;
      }

      // If neither left nor right produced a violation,
      // this subtree is valid.
      return nullptr;
   }
};

#endif
