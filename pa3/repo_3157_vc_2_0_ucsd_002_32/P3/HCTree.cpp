/* Filename: HCTree.cpp
 * Author: Yuchun Li(A53063718), Leidan Chen(A53079699)
 * Date: Feb 13, 2015
 * Description:
 */

#include <stack>
#include "HCTree.hpp"


using namespace std;

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){
  priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
  vector<int>::const_iterator vit = freqs.begin();
  vector<int>::const_iterator ven = freqs.end();
  
  /* Create new HCNode for new symbol and put it into priority queue */
  for (byte i=0; vit!=ven ; ++vit, ++i) {
    if (*vit != 0) {
      HCNode* n = new HCNode(*vit, i, 0, 0, 0);
      pq.push(n);
    }
  }
  /* Only one node in priority queue */
  if (pq.size() == 1) {
    root = pq.top();
    leaves[(int)root->symbol] = root;
    pq.pop();
    return;
  }
  
  while (pq.size() != 0) {
    /* Stops if there is only one node in priority queue */
    if (pq.size() == 1) {
      root = pq.top();
      pq.pop();
      return;
    }
    
    HCNode* n1 = pq.top();
    pq.pop();
    HCNode* n2 = pq.top();
    pq.pop();
    
    /* update the leaves vector */
    if (n1->c0 == 0 && n1->c1 == 0) {
      leaves[(int) n1->symbol] = n1;
    }
    if (n2->c0 == 0 && n2->c1 == 0) {
      leaves[(int) n2->symbol] = n2;
    }
    
    /* Merge the node. Smaller symbol as left child
     * and larger symbol as right child
     */
    HCNode* mergeNode;
    if (n1->symbol > n2->symbol) {
      mergeNode = new HCNode(n1->count + n2->count,\
                             n2->symbol, n2, n1, 0);
    } else {
      mergeNode = new HCNode(n1->count + n2->count,\
                             n1->symbol, n1, n2, 0);
    }
    n1->p = mergeNode;
    n2->p = mergeNode;
    pq.push(mergeNode);
  }
  
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const{
  HCNode* temp = leaves[symbol];
  stack<int> codeStack;
  if (temp->p == 0){
    out.writeBit(0);
  }
  while (temp->p != 0) {
    if (temp->p->c0==temp) {
      codeStack.push(0);
    } else{
      codeStack.push(1);
    }
    temp=temp->p;
  }
  while(!codeStack.empty()){
    out.writeBit(codeStack.top());
    codeStack.pop();
  }
}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const{
  HCNode* temp = leaves[symbol];
  stack<byte> codeStack;
  if (temp->p == 0){
    out << '0';   // HCTree with only the root
  }
  while (temp->p != 0) {
    if (temp->p->c0==temp) {
      codeStack.push('0');
    } else{
      codeStack.push('1');
    }
    temp=temp->p;
  }
  while(!codeStack.empty()){
    out << codeStack.top();
    codeStack.pop();
  }
}


/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const{
  HCNode* curr = root;
  if (root->c0 == 0 && root->c1 == 0) {
    in.readBit();
    return (int)root->symbol;
  }
  while (curr->c0 != 0 || curr->c1 != 0) {
    if (in.readBit() == 0){
      curr = curr->c0;
    } else {
      curr = curr->c1;
    }
  }
  return (int)curr->symbol;
}

/** Return the symbol coded in the next sequence of bits (represented as
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const{
  HCNode* curr = root;
  if (root->c0 == 0 && root->c1 == 0) {
    in.get();
    return (int)root->symbol;
  }
  while (curr->c0 != 0 || curr->c1 != 0) {
    if (in.get() == '0'){
      curr = curr->c0;
    } else {
      curr = curr->c1;
    }
  }
  return (int)curr->symbol;
}

HCNode* HCTree::getRoot() const{
  return root;
}

/*
 * Description: rebuild the file using header info
 * Arguments: in - reference to ifstream to use
 * Return Value: none
 */
void HCTree::rebuild(ifstream& in){
  stack<HCNode*> myStack;
  byte flag;
  in.read((char*)&flag, sizeof(flag));
  
  /* loop until the stack size is 1 and flag meets separator*/
  while (myStack.size()>1 || flag != 0 ) {
    if (flag == 1) { // this is a leaf node
      byte symbol;
      in.read((char*)&symbol,sizeof(symbol));
      HCNode* newNode = new HCNode(0, symbol, 0, 0, 0);
      leaves[(int)symbol] = newNode;
      myStack.push(newNode);
    } else if(!myStack.empty()){ // this is a internal node
      HCNode* c1 = myStack.top();
      myStack.pop();
      HCNode* c0 = myStack.top();
      myStack.pop();
      HCNode* mergeNode = new HCNode(0, 0, c0, c1, 0);
      c0->p = mergeNode;
      c1->p = mergeNode;
      myStack.push(mergeNode);
    }
    in.read((char*)&flag, sizeof(flag));
  }
  root = myStack.top();
  myStack.pop();
}

/*
 * Description: postorder delete all the HCNodes
 * Arguments: n - the starting HCNode
 * Return Value: none
 */
void HCTree::deleteAll(HCNode* n) {
  if (n == 0) return;
  if (n->c0 != 0) deleteAll(n->c0);
  if (n->c1 != 0) deleteAll(n->c1);
  delete n;
}



