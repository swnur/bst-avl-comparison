#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <stack>

struct Node {
   Node* left;
   Node* right;
   int value;
   int height;

   Node(int _value): value(_value), left(nullptr), right(nullptr), height(0) {}
};

class AVLTree {
private:
   Node* root;

   void printRecursive(Node* node, int indent = 0) const {
      if (node != nullptr) {
         printRecursive(node->right, indent + 5);
         for (int i = 0; i < indent; ++i) {
            std::cout << " ";
         }
         std::cout << "|-->" << node->value << "(" << node->height << ")" << std::endl;
         printRecursive(node->left, indent + 4);
      }
   }

   int subtree_height(Node* ptr) {
      if (ptr == nullptr) {
         return 0;
      }
      return ptr->height;
   }

   int balance(Node* ptr) {
      return subtree_height(ptr->right) - subtree_height(ptr->left);
   }

   void delete_tree(Node* root) {
      if (root != nullptr) {
         delete_tree(root->left);
         delete_tree(root->right);
         delete root;
      }
   }
public:
   AVLTree(): root(nullptr) {}

   ~AVLTree() {
      delete_tree(root);
   }

   void insert(int val) {
      std::stack<Node*> path;
      Node* parent = nullptr;
      Node* curr = root;
      while(curr != nullptr) {
         path.push(curr);
         if (val < curr->value) {
            parent = curr;
            curr = curr->left;
         } else {
            parent = curr;
            curr = curr->right;
         }
      }

      Node* inserted = new Node(val);

      if (parent == nullptr) {
         root = inserted;
         path.push(root);
      } else {
         if (val <= parent->value) {
            parent->left = inserted;
            path.push(parent->left);
         } else {
            parent->right = inserted;
            path.push(parent->right);
         }
      }

      while(!path.empty()) {
         Node* tmp = path.top();
         path.pop();
         tmp->height = 1 + std::max(subtree_height(tmp->left), subtree_height(tmp->right));
      }
   }

   bool find(int val) {
      Node* curr = root;
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