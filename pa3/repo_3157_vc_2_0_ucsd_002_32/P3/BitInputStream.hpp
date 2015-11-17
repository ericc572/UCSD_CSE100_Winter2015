/* Filename: BitInputStream.hpp
 * Author: Yuchun Li(A53063718), Leidan Chen(A53079699)
 * Date: Feb 22, 2015
 */

#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

using namespace std;

class BitInputStream {
private:
  char buf;    // one byte buffer of bits
  int nbits;   // how many bits have been read from buf
  istream& in; // the input stream to use
public:
  BitInputStream(istream& is) : in(is), buf(0), nbits(8){};
  void fill();
  int readBit();
};

#endif
