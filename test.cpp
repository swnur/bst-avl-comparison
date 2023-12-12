#include <iostream>
#include "AVL.hpp"
#include "BST.hpp"

int main() {
   Tree bst_tree;

   bst_tree.insert(10);
   bst_tree.insert(5);
   bst_tree.insert(3);
   bst_tree.insert(7);
   bst_tree.insert(15);
   bst_tree.insert(11);
   bst_tree.insert(20);
   
   if (bst_tree.find(3)) {
      std::cout << "3 is in the tree." << std::endl;
   } else {
      std::cout << "3 is not in the tree." << std::endl;
   }
   
   bst_tree.print();
   
}