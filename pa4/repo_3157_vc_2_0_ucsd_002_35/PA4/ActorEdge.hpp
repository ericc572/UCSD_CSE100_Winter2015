/**
 * ActorEdge.hpp
 * Author: Yuchun Li (A53063718)
 * Date: Feb. 28, 2015
 */

#ifndef ACTOREDGE_HPP
#define ACTOREDGE_HPP

#include <queue>

using namespace std;
class ActorNode;
class Movie;
class ActorEdge{
public:
  ActorNode* from;
  ActorNode* to;
  Movie* mov;
  
  ActorEdge(ActorNode* f, ActorNode* t, Movie* m) : from(f),to(t),mov(m) {};
};

#endif // ACTOREDGE_HPP