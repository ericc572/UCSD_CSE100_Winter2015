#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    deleteAll(root);
    root = 0;
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO
  virtual bool insert(const Data& item) {
    // Create a new node for insertion.
    BSTNode<Data> *newNode = new BSTNode<Data> (item);
    // If there is no root, then let the new node be the root.
    if (root == 0){        
      root = newNode;
      isize = 1;
      return true;
    } else {
      BSTNode<Data> *currentNode = root; // In the case that there is a root.
      while (currentNode != 0){
        // If the new node's key is less, and the current node's left 
        // child is 0, then assign the current node's left child with 
        // the new node.
        if (item < currentNode->data){      
          if (currentNode->left == 0){      
            currentNode->left = newNode;
            newNode->parent = currentNode;
            isize++;
            currentNode = 0;
          } else {     
            // If the left child not 0, continue searching for a proper
	    // location by assigning the current node with that child.
            currentNode = currentNode->left;
          }
        } 
          // Similarly, if greater, and the right child is 0, then assign
	  // the current node's right child with the new node.
	 else if (currentNode->data < item){
            if (currentNode->right == 0){
              currentNode->right = newNode;
              newNode->parent = currentNode;
              isize++;
              currentNode = 0;
            } else {
            // If the right child not 0, continue searching for a proper
	    // location by assigning the current node with that child.
              currentNode = currentNode->right;
            }
        } else {
          // false if an item equal to this one was already in this BST
          delete newNode;   // already exists, delete to relieve the heap.
          return false;
        }
      }
      return true;
    }
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO
  iterator find(const Data& item) const {
    BSTNode<Data> *currentNode = root;   // Start from the root.
    while(currentNode != 0){	
      if (item < currentNode->data){  // key is less, assign it with left
        currentNode = currentNode->left;
      } else if (currentNode->data < item){ // greater, assign it with right
        currentNode = currentNode->right;
      } else {
        
	return typename BST<Data>::iterator(currentNode); // matching node found
      }
    }
    return typename BST<Data>::iterator(0); // matching node not found
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    return isize == 0;
  }

  /** Return an iterator pointing to the first item in the BST (not the root).
   */ // TODO
  iterator begin() const {
    BSTNode<Data> *currentNode = root;  
    while(currentNode->left != 0){     // keep searching the leftmost node.
      currentNode = currentNode->left;
    }
    return typename BST<Data>::iterator(currentNode);
    //return typename BST<Data>::iterator(root->leftmostchild());
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:

  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
   */ // TODO
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
      if current node is null: return;
      recursively traverse left sub-tree
      print current node data
      recursively traverse right sub-tree
    */
    if (n == 0){
      return;
    }
    if (n->left != 0){
      inorder(n->left);     // recursively descend into left subtree
    }
    std::cout << *n <<std::endl;  // When left done, current is printed. 
    if (n->right != 0){
      inorder(n->right);      // recursively descend into right subtree
    }
  }

  /** Find the first element of the BST
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  /** do a postorder traversal, deleting nodes
   */ // TODO
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
    */
    if (n == 0){
      return;
    }
    if (n->left != 0){
      deleteAll(n->left);
    }
    if (n->right != 0){
      deleteAll(n->right);
    }
    if (n->parent == 0){        // root has no parent
    } else if (n->parent->left == n){     // current is left
      n->parent = 0;
    } else if (n->parent->right == n) {   // current is right
      n->parent = 0;
    }
    delete n;
  }
 };


#endif //BST_HPP
