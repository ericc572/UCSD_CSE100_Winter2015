/**
 * Movie.hpp
 * Author: Yuchun Li (A53063718)
 * Date: Feb. 28, 2015
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include "ActorEdge.hpp"

using namespace std;

class Movie{
public:
  vector<ActorNode*> * actors;
  string title;
  int year;
  int numOfUnmergedSet;
  
  Movie(string t, int y) : title(t), year(y), numOfUnmergedSet(0) {
    actors = new vector<ActorNode*>();
  }
  
  ~Movie(){
    delete actors;
  }
  
  int weight(){
    return 1 + 2015 - year;
  }
  
  bool operator<(const Movie& other){
    if (year != other.year) return year < other.year;
    return title.compare(other.title) < 0;
  }
};

class MoviePtrLess{
public:
  bool operator()(Movie* const & lhs, Movie* const & rhs) const{
    return *lhs < *rhs;
  }
};

#endif // MOVIE_HPP