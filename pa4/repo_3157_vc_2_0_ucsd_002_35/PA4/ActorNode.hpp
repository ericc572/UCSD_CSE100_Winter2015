/**
 * ActorNode.hpp
 * Author: Yuchun Li (A53063718)
 * Date: Feb. 28, 2015
 */

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <unordered_map>
#include <string>
#include <climits>
#include "Movie.hpp"

using namespace std;

class ActorNode{
public:
  unordered_map<string, ActorEdge*> * adj;
  ActorNode* prev;
  string name;
  int dist;
  bool visited;
  
  ActorNode(string n,int d) : prev(0),name(n),dist(d),visited(false) {
    adj = new unordered_map<string, ActorEdge*>();
  }
  
  ~ActorNode(){
    deleteAll();
    delete adj;
  }
  
  /*
   * Description: Initialize the instance variables
   * Arguments: none
   * Return Value: none
   */
  void initialize(){
    prev = 0;
    dist = INT_MAX;
    visited = false;
  }
  
  /*
   * Description: Delete the ActorEdge objects in adjacency list
   * Arguments: none
   * Return Value: none
   */
  void deleteAll(){
    unordered_map<string, ActorEdge*>::iterator ait = adj->begin();
    unordered_map<string, ActorEdge*>::iterator aen = adj->end();
    for(; ait != aen; ++ait){
      delete ait->second;
    }
  }
  
  bool operator<(const ActorNode& other){
    if (dist != other.dist) return dist > other.dist;
    return name.compare(other.name) > 0;
  }
};

class ActorNodePtrLess{
public:
  bool operator()(ActorNode* const & lhs, ActorNode* const & rhs) const{
    return *lhs < *rhs;
  }
};

#endif // ACTORNODE_HPP
