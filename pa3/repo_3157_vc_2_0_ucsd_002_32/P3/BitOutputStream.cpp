/* Filename: BitOutputStream.cpp
 * Author: Yuchun Li(A53063718), Leidan Chen(A53079699)
 * Date: Feb 22, 2015
 */

#include "BitOutputStream.hpp"

using namespace std;

/*
 * Description: flush buffer to ostream
 * Arguments: none
 * Return Value: none
 */
void BitOutputStream::flush(){
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/*
 * Description: write a bit to buffer
 * Arguments: the bit need to write to buffer
 * Return Value: none
 */
void BitOutputStream::writeBit(int i){
  if (nbits == 8) flush();
  buf |= (i & 1) << nbits;
  nbits++;
}

/*
 * Description: check if nbits is 0
 * Arguments: none
 * Return Value: true - if nbits is zero
 *               false - if nbits is not zero
 */
bool BitOutputStream::isEmpty(){
  return nbits == 0;
}