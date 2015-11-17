/**
 * moviespan.cpp
 * Author: Yuchun Li (A53063718)
 * Date: Feb. 28, 2015
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "ActorGraph.hpp"
#include "DisjointSet.hpp"

using namespace std;

/*
 * Description: print the usage information
 * Arguments: argv[] - command line arguments
 * Return Value: none
 */
void printUsage(char* argv[]){
  cerr << "\tERROR: Incorrect arguments" << endl
  << "\tUsage: " << argv[0] << " movie_cast_tsv_file output_cast_tsv_file" << endl;
}

int main (int argc, char** argv){
  if (argc < 3) {
    printUsage(argv);
    return EXIT_FAILURE;
  }
  
  ActorGraph act;
  ofstream out(argv[2]);
  unordered_map<string, Movie*> * outMovie = new unordered_map<string, Movie*>();
  
  if (!out.is_open()){
    cerr << "Cannot open" << argv[4] << endl;
    return EXIT_FAILURE;
  }
  
  out << "Actor/Actress\tMovie\tYear" << endl;
  act.loadFromFile(argv[1]);
  
  DisjointSet djtSet(act.getGraphMap());
  
  while (djtSet.numOfSets() > 1) {
    unordered_map<string, Movie*>::iterator mit = act.getMovieMap()->begin();
    unordered_map<string, Movie*>::iterator men = act.getMovieMap()->end();
    Movie* bestMovie = mit->second;
    for ( ; mit != men; ++mit) {
      vector<ActorNode*>::iterator ait = mit->second->actors->begin();
      vector<ActorNode*>::iterator aen = mit->second->actors->end();
      mit->second->numOfUnmergedSet = 0;
      /* Compute the number of unmerged set */
      vector<ActorNode*> unmergedSets;
      for ( ; ait != aen; ++ait) {
        ActorNode* root = djtSet.find(*ait);
        vector<ActorNode*>::iterator uit = unmergedSets.begin();
        vector<ActorNode*>::iterator uen = unmergedSets.end();
        bool exists = false;
        for (; uit != uen; ++uit){
          if (*uit == root) exists = true;
        }
        if (!exists) unmergedSets.push_back(root);
      }
      mit->second->numOfUnmergedSet = unmergedSets.size();
      /* Find the best movie according to its number of unmerged nodes */
      if (mit->second->numOfUnmergedSet >= bestMovie->numOfUnmergedSet) {
        bestMovie = mit->second;
      }
    }
    /* Merge all the casts in the best movie into one set */
    vector<ActorNode*>::iterator ait = bestMovie->actors->begin();
    vector<ActorNode*>::iterator aen = bestMovie->actors->end();
    while (ait != aen) {
      ActorNode* curr = *ait;
      if (++ait == aen) break;
      ActorNode* next = *ait;
      djtSet.merge(curr, next);
    }
    string str = bestMovie->title + to_string(bestMovie->year);
    // Insert the best movie to outMovie table
    outMovie->insert(make_pair(str,bestMovie));
    // Delete the best movie from the movies table
    act.getMovieMap()->erase(str);
  }

  /* Output the movies set to the result file */
  unordered_map<string, Movie*>::iterator mit = outMovie->begin();
  unordered_map<string, Movie*>::iterator men = outMovie->end();
  for ( ; mit != men; ++mit) {
    vector<ActorNode*>::iterator ait = mit->second->actors->begin();
    vector<ActorNode*>::iterator aen = mit->second->actors->end();
    for ( ; ait != aen; ++ait) {
      out << (*ait)->name << "\t"
          << mit->second->title << "\t"
          << mit->second->year << endl;
    }
    delete mit->second;
  }
  cout << "Uses " << outMovie->size() << " movies to connect all actors!" << endl;

  delete outMovie;
  return EXIT_SUCCESS;
}






















