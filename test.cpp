#include <iostream>
#include "AVL.hpp"
#include "BST.hpp"

int main() {
   AVLTree tree;

   tree.insert(10);
   tree.insert(5);
   tree.insert(20);
   tree.insert(3);
   tree.insert(7);
   tree.insert(15);
   tree.insert(27);
   tree.insert(1);
   tree.insert(6);
   tree.insert(11);
   tree.insert(18);
   tree.insert(26);
   tree.insert(30);
   tree.insert(0);
   
   
   if (tree.find(3)) {
      std::cout << "3 is in the tree." << std::endl;
   } else {
      std::cout << "3 is not in the tree." << std::endl;
   }

   // tree.print();
}