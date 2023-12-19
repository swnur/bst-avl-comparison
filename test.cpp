#include <iostream>
#include "AVL.hpp"
#include "BST.hpp"

int main() {
   AVLTree avl_tree;
   BSTree bs_tree;

   std::vector<int> test_arr_right_heavy = {1, 2, 3, 4, 5, 6, 7};
   std::vector<int> test_arr_left_heavy = {7, 6, 5, 4, 3, 2, 1};
   std::vector<int> test_arr_large = {50, 25, 75, 10, 40, 60, 90, 5, 20, 30, 45, 55, 70, 80, 95};

   
   std::vector<std::string> list_of_words = {"z", "apple", "banana", "potato", "patates", "tomato", "pomidor", "grapefruit", "g"};
   
   for(const auto& word: list_of_words) {
      avl_tree.insert(word);
      bs_tree.insert(word);
   }

   if (avl_tree.find("apple")) {
      std::cout << "apple is in the tree." << std::endl;
   } else {
      std::cout << "apple is not in the tree." << std::endl;
   }

   if (bs_tree.find("apple")) {
      std::cout << "apple is in the tree." << std::endl;
   } else {
      std::cout << "apple is not in the tree." << std::endl;
   }

   std::cout << "AVL Tree" << std::endl;
   avl_tree.print();
  
   std::cout << "BS Tree" << std::endl;
   bs_tree.print();
}