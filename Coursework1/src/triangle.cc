//! \author Stephen McGruer

#include "./triangle.h"

namespace computer_animation {

void Triangle::SetEdges(int e1, int e2, int e3) {
  edges_[0] = e1;
  edges_[1] = e2;
  edges_[2] = e3;
}
}
