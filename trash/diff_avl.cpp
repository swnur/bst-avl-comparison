#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <random>
#include "AVL.hpp"
#include "BST.hpp"

using ns = std::chrono::nanoseconds;

void fill_list(std::vector<std::string>& list, std::fstream& file) {
   for (int i = 0; i < list.size(); ++i) {
      file >> list[i];
   }
   std::sort(list.begin(), list.end());
}  

void run_measurements(int number_of_words, int max_times, std::vector<std::string>& list_of_words, std::ostream& file_out) {
   file_out << "Size AVL-IterInsert AVL-RecurInsert" << std::endl;

   std::vector<ns> totals_insert_avl_iter(number_of_words);
   std::vector<ns> totals_insert_avl_recur(number_of_words);;

   for (int times = 0; times < max_times; ++times) {
      AVLTree avl_tree;

      for(int size = 0; size < number_of_words; ++size) {
            auto start = std::chrono::steady_clock::now();
            avl_tree.insert_iter(list_of_words[size]);
            auto end = std::chrono::steady_clock::now();
            ns time_taken = std::chrono::duration_cast<ns>(end - start);

            totals_insert_avl_iter[size] += time_taken;

            start = std::chrono::steady_clock::now();
            avl_tree.insert(list_of_words[size]);
            end = std::chrono::steady_clock::now();
            time_taken = std::chrono::duration_cast<ns>(end - start);
      
            totals_insert_avl_recur[size] += time_taken;
      }
   }

   for (int size = 0; size < number_of_words; ++size) {
      file_out << size + 1 << " " << totals_insert_avl_iter[size].count() / max_times  
               << " " << totals_insert_avl_recur[size].count() / max_times << std::endl;
   }
}

int main(int argc, char* argv[]) {
   const int number_of_words = 100000;
   const int max_times = 100;

   int measurement_case = 0;

   if (argc > 1) {
      measurement_case = std::atoi(argv[1]);
   }

   std::vector<std::string> list_of_words(number_of_words);
   std::fstream dictionary;
   dictionary.open("dictionary.txt");

   std::ofstream output_file("graphs/results_avl_insert.txt");
   
   if (!dictionary.is_open()) {
      std::cerr << "Error opening file." << std::endl;
   }

   fill_list(list_of_words, dictionary);

   std::vector<std::string> randomized_list = list_of_words; // Randomized list of words
   std::vector<std::string> partially_sorted_list = list_of_words; // Partially sorted list of words

   std::random_device rd;
   std::mt19937 gen(rd());

   // for(int i = 0, j = partially_sorted_list.size() - 1; i < j; i += 100, j -= 100) {
   //    std::swap(partially_sorted_list[i], partially_sorted_list[j]);
   // }

   int swap_increment = 1000;
   for (int i = 0; i < number_of_words - swap_increment; i += swap_increment) {
      std::uniform_int_distribution<int> dist(i + 1, number_of_words - 1);
      int j = dist(gen);
      int k = dist(gen);
      std::swap(partially_sorted_list[j], partially_sorted_list[k]);
   } 

   std::shuffle(randomized_list.begin(), randomized_list.end(), gen);
  
   auto start = std::chrono::steady_clock::now();
   run_measurements(number_of_words, max_times, list_of_words, output_file);
   auto end = std::chrono::steady_clock::now();

   ns total_time = std::chrono::duration_cast<ns>(end - start);
   std::cout << total_time.count() << std::endl;
   dictionary.close();
}