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

   int subtree_height(Node* ptr) {
      if (ptr == nullptr) {
         return 0;
      }
      return ptr->height;
   }

   Node* rotate_left(Node** ptr) {
      Node* tmp = *ptr;
      Node* banana = (*ptr)->right;
      Node* potato = banana->left;

      banana->left = tmp; 
      tmp->right = potato;

      update_height(&tmp);
      update_height(&banana);

      return banana;
   }

   Node* rotate_right(Node** ptr) {
      Node* tmp = *ptr;
      Node* banana = (*ptr)->left;
      Node* potato = banana->right;

      banana->right = tmp; 
      tmp->left = potato;

      update_height(&tmp);
      update_height(&banana);

      return banana;
   }

   int balance(Node* ptr) {
      return subtree_height(ptr->right) - subtree_height(ptr->left);
   }

   void update_height(Node** ptr) {
      (*ptr)->height = 1 + std::max(subtree_height((*ptr)->left), subtree_height((*ptr)->right));
   }

   void printRecursive(Node* ptr, int indent = 0) {
      if (ptr != nullptr) {
         printRecursive(ptr->right, indent + 5);
         for (int i = 0; i < indent; ++i) {
            std::cout << " ";
         }
         int diff = balance(ptr);
         std::cout << "|-->" << ptr->value << "(" << ptr->height << ")" << std::endl;
         printRecursive(ptr->left, indent + 4);
      }
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
      std::stack<Node**> path;
      Node** ptr = &root;

      while((*ptr) != nullptr) {
         path.push(ptr);
         if ((*ptr)->value > val) {
            ptr = &((*ptr)->left);
         } else {
            ptr = &((*ptr)->right);
         }
      }

      *ptr = new Node(val);
      path.push(ptr);

      while(!path.empty()) {
         Node** tmp = path.top();
         path.pop();
         update_height(tmp);
         int diff = balance((*tmp));
         // std:: cout << (*tmp)->value << " ";

      }
      // std::cout << std::endl;
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

   void rotate_right() {
      root = rotate_right(&root);
   }

   void rotate_left() {
      root = rotate_left(&root);
   }

   void print() {
      printRecursive(root);
   }
};

#endif