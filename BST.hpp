#ifndef BST_HPP
#define BST_HPP

#include <iostream>

struct TreeNode {
   TreeNode* left;
   TreeNode* right;
   int value;

   TreeNode(int val): value(val), left(nullptr), right(nullptr) {}
};

class Tree {
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

   void delete_tree(TreeNode* root) {
      if (root != nullptr) {
         delete_tree(root->left);
         delete_tree(root->right);
         delete root;
      }
   }
public:
   Tree(): root(nullptr) {}

   ~Tree() {
      delete_tree(root);
   }

   void insert(int val) {
      TreeNode* parent = nullptr;
      TreeNode* curr = root;
      while(curr != nullptr) {
         if (val < curr->value) {
            parent = curr;
            curr = curr->left;
         } else {
            parent = curr;
            curr = curr->right;
         }
      }

      TreeNode* inserted = new TreeNode(val);

      if (parent == nullptr) {
         root = inserted;
      } else {
         if (val <= parent->value) {
            parent->left = inserted;
         } else {
            parent->right = inserted;
         }
      }
   }

   void insert_two_ptr(int val) {
      TreeNode** ptr = &root;

      while((*ptr) != nullptr) {
         if ((*ptr)->value > val) {
            ptr = &((*ptr)->left);
         } else {
            ptr = &((*ptr)->right);
         }
      }

      *ptr = new TreeNode(val);
   }

   bool find(int val) {
      TreeNode* curr = root;
      while(curr != nullptr) {
         if (val == curr->value) {
            return true;
         } else if (val < curr->value) {
            curr = curr->left;
         } else if (val > curr->value) {
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