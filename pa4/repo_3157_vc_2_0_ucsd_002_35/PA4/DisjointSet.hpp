/**
 * DisjointSet.hpp
 * Author: Yuchun Li (A53063718)
 * Date: Feb. 28, 2015
 */

#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP

#include "ActorGraph.hpp"

class DisjointSet{
private:
  unordered_map<string, ActorNode*> * djtSet;
  int size;

public:
  DisjointSet(unordered_map<string, ActorNode*> * s) : djtSet(s) {
    size = djtSet->size();
  };
  
  /*
   * Description: find the root of the actor a
   * Arguments: a - the actor need to be found
   * Return Value: none
   */
  ActorNode* find(ActorNode* a);
  
  /*
   * Description: Merge two node into one set
   * Arguments: a1 - the actor 1
   *            a2 - the actor 2
   * Return Value: none
   */
  void merge(ActorNode* a1, ActorNode* a2);
  
  /*
   * Description: Return the number of independent set
   * Arguments: none
   * Return Value: number of independent set
   */
  int numOfSets();
  
  /*
   * Description: Check if actor a is a single node in a set
   * Arguments: a - the actor need to be checked
   * Return Value: true - a is a single node in a set
   *               false - a is not a single node in a set
   */
  bool isSingleNodeSet(ActorNode* a);
  
};

#endif // DISJOINTSET_HPP

