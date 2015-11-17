/**
 * pathfinder.cpp
 * Author: Yuchun Li (A53063718)
 * Date: Feb. 28, 2015
 */

#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <fstream>
#include <sstream>
#include "ActorGraph.hpp"

using namespace std;

/*
 * Description: print the usage information
 * Arguments: argv[] - command line arguments
 * Return Value: none
 */
void printUsage(char* argv[]){
  cerr << "Usage: " << argv[0] << " rawDataFile [u|w] queryFile resultFile" << endl
  << "\trawDataFile: movie casts file" << endl
  << "\t[u|w]: unweighted or weighted graph" << endl
  << "\tqueryFile: file containing pairs of actors you are looking for" << endl
  << "\tresultFile: file containing the shortest path between each tested pair" << endl;
}

/*
 * Description: Find the path from the source actor to the target actor
 *              and output the path to the ofstream  
 * Arguments: theGraph - the whole graph
 *            from - the name of the source actor
 *            to - the name of the target actor
 *            out - reference to the ofstream
 * Return Value: none
 */
void findPath(unordered_map<string ,ActorNode*> * theGraph,\
              string from, string to, ofstream& out){
  unordered_map<string ,ActorNode*>::iterator ait = theGraph->find(to);
  ActorNode* currActor = ait->second;
  stack<ActorNode*> * actorStack = new stack<ActorNode*>();
  while (currActor->name.compare(from) != 0) {
    actorStack->push(currActor);
    currActor = currActor->prev;
  }
  while (!actorStack->empty()) {
    ActorNode* nextActor = actorStack->top();
    actorStack->pop();
    unordered_map<string, ActorEdge*>::iterator eit = \
      currActor->adj->find(currActor->name + nextActor->name);
    Movie* connMovie = eit->second->mov;
    out << "(" + currActor->name + ")" + "--[" \
      + connMovie->title + "#@" + to_string(connMovie->year) + "]-->";
    currActor = nextActor;
  }
  out << "(" + currActor->name + ")" << endl;
  delete actorStack;
}

int main (int argc, char** argv){
  if (argc < 5) {
    printUsage(argv);
    return EXIT_FAILURE;
  }
  
  ActorGraph act;
  ifstream in(argv[3]); // Query request file 
  ofstream out(argv[4]);// Result file
  
  if (!in.is_open()){
    cerr << "Cannot open" << argv[3] << endl;
    return EXIT_FAILURE;
  }
  
  if (!out.is_open()){
    cerr << "Cannot open" << argv[4] << endl;
    return EXIT_FAILURE;
  }
  
  out << "(actor)--[movie#@year]-->(actor)--..." << endl;
  act.loadFromFile(argv[1]);
  bool have_header = false;
  while (in) {
    string s, fromActor, toActor;
    if (!getline(in, s)) break;
    if (!have_header) {
      have_header = true;
      continue;
    }
    istringstream ss(s);
    getline(ss, fromActor, '\t');
    getline(ss, toActor, '\t');
    act.initialize();
    if (strcmp(argv[2],"u") == 0) {
      act.BFSTraverse(fromActor, toActor);
    } else {
      act.dijkstraTraverse(fromActor, toActor);
    }
    findPath(act.getGraphMap(), fromActor, toActor, out);
  }
  in.close();
  out.close();
  return EXIT_SUCCESS;
}
