/* Filename: BitOutputStream.hpp
 * Author: Yuchun Li(A53063718), Leidan Chen(A53079699)
 * Date: Feb 22, 2015
 */

#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitOutputStream {
private:
  char buf;     // one byte buffer of bits
  int nbits;    // how many bits have been written to buf
  ostream& out; // reference to the output stream to use
public:
  BitOutputStream(ostream& os) : out(os), buf(0), nbits(0){};
  void flush();
  void writeBit(int i);
  bool isEmpty();
};

#endif
