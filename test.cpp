#include <iostream>
#include "AVL.hpp"
#include "BST.hpp"

int main() {
   AVLTree tree;

   std::vector<int> test_arr_right_heavy = {1, 2, 3, 4, 5, 6, 7};
   std::vector<int> test_arr_left_heavy = {7, 6, 5, 4, 3, 2, 1};
   std::vector<int> test_arr_large = {50, 25, 75, 10, 40, 60, 90, 5, 20, 30, 45, 55, 70, 80, 95};

   for (const auto& num: test_arr_large) {
      tree.insert(num);
   }
   
   
   if (tree.find(3)) {
      std::cout << "3 is in the tree." << std::endl;
   } else {
      std::cout << "3 is not in the tree." << std::endl;
   }

   // tree.print();
}