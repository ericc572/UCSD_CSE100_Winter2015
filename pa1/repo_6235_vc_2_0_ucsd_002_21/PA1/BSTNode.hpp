#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

template<typename Data>
class BSTNode {

public:

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d) : data(d) {
    left = right = parent = 0;
  }

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ // TODO
  BSTNode<Data>* successor() {
    if (right != 0){                // If the right child exists,
                                    // its left-most child is the successor.
      return right->leftmostchild();
    } else {                        // The right child doesn't exist.
      BSTNode<Data>* parentNode = parent;
      BSTNode<Data>* currentNode = this;
      if (parentNode == 0){
        return 0;
      }
      while(parentNode->left != currentNode){   // Parent exists; current
                                                // node is not the parent's
                                                // left child.
        currentNode = parentNode;
        parentNode = parentNode->parent;        // keep looking for the
                                                // greater parent
        if (parentNode == 0){                   // no such parent exists
          return 0;
        }
      }
      return parentNode;      // current node is the parent's left child,
                              // then the parent is the successor.
    }
  }

private:
  BSTNode<Data>* leftmostchild(){           // locate the left-most child.
    BSTNode<Data>* currentNode = this;
    while(currentNode->left != 0){
      currentNode = currentNode->left;
    }
    return currentNode;
  }

}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}
#endif // BSTNODE_HPP
