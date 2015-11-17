/* Filename: BitInputStream.cpp
 * Author: Yuchun Li(A53063718), Leidan Chen(A53079699)
 * Date: Feb 22, 2015
 */

#include "BitInputStream.hpp"

using namespace std;

/*
 * Description: fill the buffer
 * Arguments: none
 * Return Value: none
 */
void BitInputStream::fill(){
  buf = in.get();
  nbits = 0;
}

/*
 * Description: read a bit from buf
 * Arguments: none
 * Return Value: the bit at current position
 */
int BitInputStream::readBit(){
  if (nbits == 8) fill();
  int bit  = buf & (1 << nbits);
  nbits++;
  return (bit>0 ? 1 : 0);
}




