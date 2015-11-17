/**
 * DisjointSet.cpp
 * Author: Yuchun Li (A53063718)
 * Date: Feb. 28, 2015
 */
#include <cstdlib>
#include "DisjointSet.hpp"

using namespace std;

ActorNode* DisjointSet::find(ActorNode* a){
  if (a->prev == 0) return a;
  ActorNode* next = a;
  while (next->prev != 0) {
    next = next->prev;
  }
  // compress the path to root to optimized the find opertaion
  a->prev = next; 
  return next;
}

void DisjointSet::merge(ActorNode* a1, ActorNode* a2){
  ActorNode* root1 = find(a1);
  ActorNode* root2 = find(a2);
  if (root1 == root2) return; // Already in the same set
  if (abs(root1->dist) > abs(root2->dist)) {
    root2->prev = root1;
    root1->dist += root2->dist;
  } else {
    root1->prev = root2;
    root2->dist += root1->dist;
  }
  size--;
}

int DisjointSet::numOfSets(){
  return size;
}

bool DisjointSet::isSingleNodeSet(ActorNode* a){
  return a->prev == 0;
}