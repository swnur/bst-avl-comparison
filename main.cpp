#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <fstream>
#include <chrono>
#include <random>
#include "AVL.hpp"
#include "BST.hpp"

using ns = std::chrono::nanoseconds;

void fill_list(std::vector<std::string>& list, std::fstream& file) {
   for(int i = 0; i < list.size(); ++i) {
      file >> list[i];
   }
}  

void run_measurements(int number_of_words, int max_times, int step, std::vector<std::string>& list_of_words, std::ostream& file_out) {
   ns total_time_bst_insert = ns(0);
   ns total_time_bst_find = ns(0);
   ns total_time_avl_insert = ns(0);
   ns total_time_avl_find = ns(0);

   file_out << "Size BST-Insert BST-Find AVL-Insert ABL-Find" << std::endl;

   for (int i = step; i <= number_of_words; i += step) {
      if (i == 1000) 
         step = 500;
      else if (i == 10000) 
         step = 1000;

      for (int i = 0; i < max_times; ++i) {
         AVLTree avl_tree;
         BSTree bs_tree;

         auto start = std::chrono::steady_clock::now();
         for (int j = 0; j < i; ++j) {
            avl_tree.insert(list_of_words[j]);
         }
         auto end = std::chrono::steady_clock::now();
         total_time_avl_insert += std::chrono::duration_cast<ns>(end - start);

         start = std::chrono::steady_clock::now();
         for (int j = 0; j < i; ++j) {
            bs_tree.insert(list_of_words[j]);
         }
         end = std::chrono::steady_clock::now();
         total_time_bst_insert += std::chrono::duration_cast<ns>(end - start);
      
         start = std::chrono::steady_clock::now();
         avl_tree.find(list_of_words[i / 2]);
         avl_tree.find("");
         end = std::chrono::steady_clock::now();
         total_time_avl_find += std::chrono::duration_cast<ns>(end - start);

         start = std::chrono::steady_clock::now();
         bs_tree.find(list_of_words[i / 2]);
         bs_tree.find("");
         end = std::chrono::steady_clock::now();
         total_time_bst_find += std::chrono::duration_cast<ns>(end - start);
      }

      file_out << i << " " << total_time_bst_insert.count() / max_times  
                    << " " << total_time_bst_find.count() / max_times
                    << " " << total_time_avl_insert.count() / max_times
                    << " " << total_time_avl_find.count() / max_times << std::endl;
   }
}

int main() {
   // Constants
   const int number_of_words = 250000;
   const int max_times = 100;
   const int step = 100;

   std::vector<std::string> list_of_words(number_of_words);
   std::fstream dictionary;
   dictionary.open("dictionary.txt");
   std::ofstream output_file_sorted("results_sorted.txt");
   std::ofstream output_file_part_sorted("results_part_sorted.txt");
   std::ofstream output_file_rand("results_rand.txt");
   
   if (!dictionary.is_open() || !output_file_part_sorted.is_open() 
         || !output_file_sorted.is_open() || !output_file_rand.is_open()) {
      std::cerr << "Error opening file." << std::endl;
   }

   fill_list(list_of_words, dictionary);

   std::vector<std::string> randomized_list = list_of_words; // Randomized list of words
   std::vector<std::string> partially_sorted_list = list_of_words; // Partially sorted list of words

   std::random_device rd;
   std::mt19937 gen(rd());

   // Version 1 of partining list
   for(int i = 0, j = number_of_words - 1; i < j; i += 1000, j -= 1000) {
      std::swap(partially_sorted_list[i], partially_sorted_list[j]);
   }

   /* Version 2 of partioning list
   int swap_increment = 1000;
   for (int i = 0; i < number_of_words - swap_increment; i += swap_increment) {
      std::uniform_int_distribution<int> dist(i + 1, number_of_words - 1);
      int j = dist(gen);
      std::swap(partialli_sorted_list[i], partialli_sorted_list[j]);
   } 
   */

   std::shuffle(randomized_list.begin(), randomized_list.end(), gen);

   run_measurements(number_of_words, max_times, step, list_of_words, output_file_sorted);
   run_measurements(number_of_words, max_times, step, partially_sorted_list, output_file_part_sorted);
   run_measurements(number_of_words, max_times, step, randomized_list, output_file_rand);

   dictionary.close();
}