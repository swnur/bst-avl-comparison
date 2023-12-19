#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <string>
#include <stack>

struct TreeNode {
   TreeNode* left;
   TreeNode* right;
   std::string value;

   TreeNode(std::string _value): value(_value), left(nullptr), right(nullptr) {}
};

class BSTree {
private:
   TreeNode* root;

   void printRecursive(TreeNode* node, int indent = 0) const {
      if (node != nullptr) {
         printRecursive(node->right, indent + 5);
         for (int i = 0; i < indent; ++i) {
            std::cout << " ";
         }
         std::cout << "|-->" << node->value << std::endl;
         printRecursive(node->left, indent + 4);
      }
   }

   void delete_tree(TreeNode *root) {
      std::stack<TreeNode *> ptrs;
      ptrs.push(root);

      while (!ptrs.empty()) {
         TreeNode *ptr = ptrs.top();
         ptrs.pop();
         if (ptr) {
            ptrs.push(ptr->left);
            ptrs.push(ptr->right);
            delete ptr;
         }
      }
   }
public:
   BSTree(): root(nullptr) {}

   ~BSTree() {
      delete_tree(root);
   }

   void insert(std::string _value) {
      TreeNode** ptr = &root;

      while((*ptr) != nullptr) {
         if ((*ptr)->value > _value) {
            ptr = &((*ptr)->left);
         } else {
            ptr = &((*ptr)->right);
         }
      }

      *ptr = new TreeNode(_value);
   }

   bool find(std::string _value) {
      TreeNode* curr = root;
      while(curr != nullptr) {
         if (_value == curr->value) {
            return true;
         } else if (_value < curr->value) {
            curr = curr->left;
         } else if (_value > curr->value) {
            curr = curr->right;
         }
      }

      return false;
   }

   void print() {
      printRecursive(root);
   }
};


#endif