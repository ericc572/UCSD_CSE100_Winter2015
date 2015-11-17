/* Filename: HCNode.cpp
 * Author: Yuchun Li(A53063718), Leidan Chen(A53079699)
 * Date: Feb 13, 2015
 * Description:
 */

#include "HCNode.hpp"

/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 */
bool HCNode::operator<(const HCNode& other){
  if (count != other.count) return count > other.count;
  
  return symbol < other.symbol;
}




