/*
 * ActorGraph.cpp
 * Author: Adrian Guthals
 * Date: 2/24/2015
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <utility>
#include "ActorGraph.hpp"

using namespace std;

unordered_map<string, ActorNode*> * ActorGraph::getGraphMap(){
  return theGraph;
}

unordered_map<string, Movie*> * ActorGraph::getMovieMap(){
  return movies;
}

bool ActorGraph::loadFromFile(const char* in_filename)
{
  
  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;
  
  // keep reading lines until the end of file is reached
  while (infile)
  {
    string s;
    
    // get the next line
    if (!getline( infile, s )) break;
    
    if (!have_header)
    {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss)
    {
      string next;
      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;
      
      record.push_back( next );
    }
    
    if (record.size() != 3)
    {
      // we should have exactly 3 columns
      continue;
    }
    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);
    

    Movie* m = new Movie(movie_title, movie_year);
    ActorNode* v = new ActorNode(actor_name, -1);
    // Add the new data to the graph
    createGraph(m, v);
  }
  
  if (!infile.eof())
  {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();
  
  return true;
}

void ActorGraph::createGraph(Movie* m, ActorNode* v){
  pair<unordered_map<string, ActorNode*>::iterator, bool> pActor \
    = theGraph->insert(make_pair(v->name,v));
  ActorNode* currActor = pActor.first->second;
  bool currActorExists = !pActor.second;
  if (currActorExists){
    delete v;
  }
  
  m->actors->push_back(currActor);
  pair<unordered_map<string, Movie*>::iterator, bool> pMovie \
    = movies->insert(make_pair(m->title + to_string(m->year),m));
  Movie* currMovie = pMovie.first->second;
  bool currMovieExists = !pMovie.second;
  
  if (currMovieExists) {
    vector<ActorNode*>::iterator vit = currMovie->actors->begin();
    vector<ActorNode*>::iterator ven = currMovie->actors->end();
    for (; vit != ven; ++vit){
      addEdgeToNode(currActor, *vit, currMovie);
      addEdgeToNode(*vit, currActor,  currMovie);
    }
    currMovie->actors->push_back(currActor);
    delete m;
  }
}

void ActorGraph::addEdgeToNode(ActorNode* from, ActorNode* to, Movie* mov){
  ActorEdge* e = new ActorEdge(from, to, mov);
  // create a unique string name for the new edge
  string edgeStr = from->name + to->name;
  pair<unordered_map<string, ActorEdge*>::iterator, bool> pEdge \
    = from->adj->insert(make_pair(edgeStr, e));
  ActorEdge* currEdge = pEdge.first->second;
  bool currEdgeExists = !pEdge.second;
  if (currEdgeExists) { 
    /* Always use the lightest weight movie to connect actors */
    if (currEdge->mov->year < mov->year) {
      currEdge->mov = mov;
    }
    delete e; // not a new edge
  }
}

void ActorGraph::initialize(){
  unordered_map<string ,ActorNode*>::iterator git = theGraph->begin();
  unordered_map<string ,ActorNode*>::iterator gen = theGraph->end();
  for ( ; git != gen; ++git) {
    git->second->initialize();
  }
}

void ActorGraph::BFSTraverse(string from, string to){
  // For extension only; If from == to, traverse the whole graph
  bool extension = from.compare(to) == 0;
  unordered_map<string, ActorNode*>::iterator ait = theGraph->find(from);
  ActorNode* v = ait->second;
  queue<ActorNode*> toExplore;
  v->dist = 0;
  toExplore.push(v);
  while (!toExplore.empty()) {
    ActorNode* u = toExplore.front();
    toExplore.pop();
    unordered_map<string, ActorEdge*>::iterator adjit = u->adj->begin();
    unordered_map<string, ActorEdge*>::iterator adjen = u->adj->end();
    for (; adjit != adjen; ++adjit) {
      if (adjit->second->to->dist == INT_MAX){
        adjit->second->to->dist = u->dist + 1;
        adjit->second->to->prev = u;
        if (!extension && adjit->second->to->name.compare(to) == 0) return;
        toExplore.push(adjit->second->to);
      }
    }
  }
}

void ActorGraph::dijkstraTraverse(string from, string to){
  unordered_map<string, ActorNode*>::iterator ait = theGraph->find(from);
  unordered_map<string, ActorNode*>::iterator aen = theGraph->end();
  ActorNode* v = ait->second;
  priority_queue<ActorNode*, vector<ActorNode*>,ActorNodePtrLess> toExplore;
  v->dist = 0;
  toExplore.push(v);
  while (!toExplore.empty()) {
    ActorNode* u = toExplore.top();
    toExplore.pop();
    if (u->name.compare(to) == 0) return;
    if (u->visited == true) continue;
    else u->visited = true;
    unordered_map<string, ActorEdge*>::iterator adjit = u->adj->begin();
    unordered_map<string, ActorEdge*>::iterator adjen = u->adj->end();
    for (; adjit != adjen; ++adjit) {
      if (adjit->second->to->dist > u->dist + adjit->second->mov->weight()){
        adjit->second->to->dist = u->dist + adjit->second->mov->weight();
        adjit->second->to->prev = u;
        toExplore.push(adjit->second->to);
      }
    }
  }
}

void ActorGraph::deleteAll(){
  unordered_map<string, ActorNode*>::iterator ait = theGraph->begin();
  unordered_map<string, ActorNode*>::iterator aen = theGraph->end();
  for (; ait != aen; ++ait){
    delete ait->second;
  }
  unordered_map<string, Movie*>::iterator mit = movies->begin();
  unordered_map<string, Movie*>::iterator men = movies->end();
  for (; mit != men; ++mit){
    delete mit->second;
  } 
}











