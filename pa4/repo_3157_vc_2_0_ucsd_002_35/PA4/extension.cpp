/**
 * extension.cpp
 * Author: Yuchun Li (A53063718)
 * Date: Mar 6, 2015
 * Find out the distance of all the actors to Kevin Bacon 
 */

#include <iostream>
#include <iomanip>
#include "ActorGraph.hpp"

using namespace std;

void printUsage(char* argv[]){
  cerr << "\tERROR: Incorrect arguments" << endl
  << "\tUsage: " << argv[0] << " movie_cast_tsv_file" << endl;
}

int main (int argc, char** argv){
  if (argc < 2) {
    printUsage(argv);
    return EXIT_FAILURE;
  }
  
  int sum = 0;
  ActorGraph act;
  string toActor = "BACON, KEVIN (I)";
  // keep the number of actors for each distance
  vector<int> freqs(10, 0);
  act.loadFromFile(argv[1]);

  unordered_map<string, ActorNode*>::iterator ait = act.getGraphMap()->begin();
  unordered_map<string, ActorNode*>::iterator aen = act.getGraphMap()->end();
  ActorNode* a = act.getGraphMap()->find(toActor)->second;
  act.initialize();
  act.BFSTraverse(toActor, toActor); // Traverse the whole graph
  for(; ait != aen; ++ait){
    string fromActor = ait->second->name;
    if (fromActor.compare(toActor) != 0){
      int dist = ait->second->dist;
      freqs[dist-1]++;
      sum += dist;
    }
  }
  cout << "--------------------------------" << endl;
  cout << " BACON, KEVIN (I)'s Connections " << endl;
  cout << "--------------------------------" << endl;
  cout << "   Distance\t" << "# of actors" << endl;
  vector<int>::iterator vit = freqs.begin();
  vector<int>::iterator ven = freqs.end();
  for (int i = 1; vit != ven; ++vit){
    if (*vit == 0) break;
    cout << setw(7) << i++ << "\t\t    " << *vit<< endl;
  }
  cout << "--------------------------------" << endl;
  cout << " Average distance: " << (double)sum/(act.getGraphMap()->size()-1) << endl;
  cout << "--------------------------------" << endl;
  return EXIT_SUCCESS;
}







