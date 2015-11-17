/* Filename: compress.cpp
 * Author: Yuchun Li(A53063718), Leidan Chen(A53079699)
 * Date: Feb 22, 2015
 */

#include "HCTree.hpp"
#include "HCNode.hpp"

using namespace std;

/*
 * Description: print the usage information
 * Arguments: argv[] - command line arguments
 * Return Value: none
 */
void printUsage(char* argv[]){
  cerr << "Usage: " << argv[0] << " infile outfile" << endl
       << "\tinfile: the file need to be compressed" << endl
       << "\toutfile: the compressed file" << endl;
}

/*
 * Description: post order tranversal the nodes in HCTree to build header
 *              info for reconstructing the HCTree
 * Arguments: n - the starting HCNode
 *            os - reference to ofstream to use
 * Return Value: none
 */
void postorderBuilder(HCNode* n, ofstream& os){
  if (n == 0) return;
  postorderBuilder(n->c0, os);
  postorderBuilder(n->c1, os);
  if (n->c0==0 && n->c1==0){
    byte write1 = 1;  // indicate that this is a leaf node
    os.write((char*)&write1, sizeof(write1));
    os.write((char*)&(n->symbol), sizeof(n->symbol));
  } else {
    byte write0 = 0;  // indicate that this is a non-leaf node
    os.write((char*)&write0, sizeof(write0));
  }
}

int main(int argc, char* argv[]){
  if (argc < 3) {
    printUsage(argv);
    exit(-1);
  }
  
  ifstream in (argv[1], ios::ate|ios::binary); // open with ptr at the end
  ofstream os (argv[2], ios::binary);
  BitOutputStream out(os);
  streampos end, inSize;
  vector<int> freqs(256, 0);
  HCTree* hct = new HCTree();
  int numChars = 0;
  
  end = in.tellg();
  in.seekg(0, in.beg);
  inSize = end - in.tellg(); // number of bytes in original file
  
  if (in.is_open()) {
    /* count the frequency for every character */
    for (int i=0; i<inSize; i++) {
      byte symbol = in.get();
      freqs[(int)symbol]++;
      numChars++;
    }
    
    in.seekg(0, in.beg); // move ptr to the beginning
    
    hct->build(freqs);
    
    // numChars is written to the output file at the beginning
    os.write((char*)&numChars, sizeof(numChars));
    
    postorderBuilder(hct->getRoot(), os);
    
    // insert a sperator between header info and contents
    byte sperator = 0;
    os.write((char*)&sperator, sizeof(sperator));
    
    for (int i=0; i<inSize; i++) {
      hct->encode(in.get(), out);
    }
    
    // manually flush the buf in case the buf is not empty
    if (!out.isEmpty()) {
      out.flush();
    }
    in.close();
    os.close();
  } else {
    cerr << "\tError: Cannot open infile: " << argv[1] << endl;
    exit(-1);
  }
  delete hct;
  return 0;
  
}
