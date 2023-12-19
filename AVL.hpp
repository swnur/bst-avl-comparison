#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <stack>

struct Node {
   Node* left;
   Node* right;
   std::string value;
   int height;

   Node(std::string _value): value(_value), left(nullptr), right(nullptr), height(0) {}
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

   Node* rotate_left(Node* ptr) {
      Node* tmp = ptr;
      Node* banana = ptr->right;
      Node* potates = banana->left;

      banana->left = tmp; 
      tmp->right = potates;

      update_height(&tmp);
      update_height(&banana);

      return banana;
   }

   Node* rotate_right(Node* ptr) {
      Node* tmp = ptr;
      Node* banana = ptr->left;
      Node* potates = banana->right;

      banana->right = tmp; 
      tmp->left = potates;

      update_height(&tmp);
      update_height(&banana);

      return banana;
   }

   int get_balance(Node* ptr) {
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
         int balance = get_balance(ptr);
         std::cout << "|-->" << ptr->value << "(" << balance << ")" << std::endl;
         printRecursive(ptr->left, indent + 4);
      }
   }

   void delete_tree(Node* root) {
      if (root == nullptr) {
        return;
      }

      std::stack<Node*> s;
      s.push(root);

      while (!s.empty()) {
         Node* ptr = s.top();
         s.pop();

         if (ptr->right != nullptr) {
            s.push(ptr->right);
         }
         if (ptr->left != nullptr) {
            s.push(ptr->left);
         }

         delete ptr;
      }
   }
public:
   AVLTree(): root(nullptr) {}

   ~AVLTree() {
      delete_tree(root);
   }

   void insert(std::string _value) {
      std::stack<Node**> path;
      Node** ptr = &root;

      while((*ptr) != nullptr) {
         path.push(ptr);
         if ((*ptr)->value > _value) {
            ptr = &((*ptr)->left);
         } else {
            ptr = &((*ptr)->right);
         }
      }

      *ptr = new Node(_value);
      path.push(ptr);

      while(!path.empty()) {
         Node** tmp = path.top();
         path.pop();
         update_height(tmp);
         int balance = get_balance((*tmp));

         if (balance == -2) {
            int sub_balance = get_balance((*tmp)->left);
            if (sub_balance == -1) {
               *tmp = rotate_right(*tmp);
            } else if (sub_balance == 1) {
               (*tmp)->left = rotate_left((*tmp)->left);
               *tmp = rotate_right(*tmp);
            }
         } else if (balance == 2) {
            int sub_balance = get_balance((*tmp)->right);
            if (sub_balance == 1) {
               *tmp = rotate_left(*tmp);
            } else if (sub_balance == -1) {
               (*tmp)->right = rotate_right((*tmp)->right);
               *tmp = rotate_left(*tmp);
            }
         }
      }
   }

   bool find(std::string _value) {
      Node* curr = root;
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