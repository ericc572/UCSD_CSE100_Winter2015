/*
 * ActorGraph.hpp
 * Author: Adrian Guthals
 * Date: 2/24/2015
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP


#include <unordered_map>
#include "ActorNode.hpp"
#include "ActorEdge.hpp"
#include "Movie.hpp"

using namespace std;

class ActorGraph {
protected:
  unordered_map<string, ActorNode*> * theGraph;
  unordered_map<string, Movie*> * movies;

public:
  ActorGraph(void){
    theGraph = new unordered_map<string, ActorNode*>();
    movies = new unordered_map<string, Movie*>();
  }
  
  ~ActorGraph(){
    deleteAll();
    delete theGraph;
    delete movies;
  }
  
  unordered_map<string, ActorNode*> * getGraphMap();

  unordered_map<string, Movie*> * getMovieMap();
  
  /*
   * Description: Initialize the actor in theGraph for BFS and Dijkstra
   * Arguments: none
   * Return Value: none
   */
  void initialize();

  /** You can modify this method definition as you wish
   *
   * Load the graph from a tab-delimited file of actor->movie relationships.
   *
   * in_filename - input filename
   * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
   *
   * return true if file was loaded sucessfully, false otherwise
   */
  bool loadFromFile(const char* in_filename);
  
  /*
   * Description: Add new actors and new movie to the theGrap and movies table
   * Arguments: m - possibly new movie from database
   *            v - possibly new actor from database
   * Return Value: none
   */
  void createGraph(Movie* m, ActorNode* v);

  /*
   * Description: Update actors' adjacency list
   * Arguments: from - the current actor
   *            to - the current actor's neighbour
   *            mov - movie that connectes these two actors
   * Return Value: none
   */
  void addEdgeToNode(ActorNode* from, ActorNode* to, Movie* mov);

  /*
   * Description: Traverse the theGraph using BFS
   * Arguments: from - the name of the source actor
   *            to - the name of the target actor
   * Return Value: none
   */
  void BFSTraverse(string from, string to);

  /*
   * Description: Traverse the theGraph using Dijkstra
   * Arguments: from - the name of the source actor
   *            to - the name of the target actor
   * Return Value: none
   */
  void dijkstraTraverse(string from, string to);

  /*
   * Description: Delete all the ActorNode and Movie objects
   * Arguments: none
   * Return Value: none
   */
  void deleteAll();
};


#endif // ACTORGRAPH_HPP
