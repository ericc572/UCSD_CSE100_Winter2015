/* Filename: uncompress.cpp
 * Author: Yuchun Li(A53063718), Leidan Chen(A53079699)
 * Date: Feb 22, 2015
 */

#include "HCTree.hpp"
#include "HCNode.hpp"
#include <cmath>
#include <cstdlib>

using namespace std;

/*
 * Description: print the usage information
 * Arguments: argv[] - command line arguments
 * Return Value: none
 */
void printUsage(char* argv[]){
  cerr << "Usage: " << argv[0] << " infile outfile" << endl
  << "\tinfile: the compressed file to be uncompressed" << endl
  << "\toutfile: the output file " << endl;
}

int main(int argc, char* argv[]){
  if (argc < 3) {
    printUsage(argv);
    exit(-1);
  }
  
  ifstream is (argv[1], ios::binary);
  BitInputStream in(is);
  ofstream out (argv[2],ios::binary);
  HCTree* hct = new HCTree();
  int numChars = 0; // number of characters need to be decoded

  // read the number of characters at the beginning of compressed file
  is.read((char*)&numChars, sizeof(numChars));
  
  /* check if it is empty */
  if (numChars == 0){
    delete hct;
    exit(-1);
  }
  
  hct->rebuild(is);
  
  /* write the symbols to uncompressed file */
  if (is.is_open()) {
    for (int i=0; i<numChars; i++){
      int result=hct->decode(in);
      out<<(byte) result;
    }
    is.close();
    out.close();
  }
  else{
    cerr << "\tError: Cannot open infile: " << argv[1] << endl;
    exit(-1);
  }
  
  delete hct;
  return 0;
}




