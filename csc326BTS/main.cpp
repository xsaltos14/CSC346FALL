//
//  main.cpp
//  csc326BTS
//
//  Created by xavier saltos on 11/16/25.
//

#include <iostream>      // For cout, printing text
#include "BSTNode.h"     // Node structure for the BST
#include "BSTChecker.h"  // Contains CheckBSTValidity() implementation

using namespace std;     // Allows using cout without std::cout

int main() {

   // --- BUILDING A SAMPLE BINARY SEARCH TREE ---

   // Create the root of the tree with key 50
   BSTNode* root = new BSTNode(50);

   // Create left and right children of the root
   root->left = new BSTNode(25);   // Adds a left child with key 25
   root->right = new BSTNode(75);  // Adds a right child with key 75

   // Add children under the left subtree
   root->left->left = new BSTNode(10);  // Valid: 10 < 25

   // INVALID placement: 63 > 25, but placed in left subtree of 25
   // This is meant to intentionally break BST rules
   root->left->right = new BSTNode(63);

   // Add children under the right subtree (both valid)
   root->right->left = new BSTNode(60);  // Valid: 60 < 75
   root->right->right = new BSTNode(80); // Valid: 80 > 75


   // --- CHECK THE BST FOR VALIDITY ---

   // Call the static validation function.
   // Returns:
   //   - nullptr   → if the entire tree is a valid BST
   //   - pointer   → to the FIRST node (preorder) that violates BST rules
   BSTNode* badNode = BSTChecker::CheckBSTValidity(root);


   // --- PRINT THE RESULT ---

   if (badNode) {
      // Tree is invalid, print the key of the FIRST violating node
      cout << "Invalid BST. First node in violation: "
           << badNode->key << endl;
   }
   else {
      // Tree satisfies all BST rules
      cout << "Valid BST." << endl;
   }

   return 0;  // End of program
}
