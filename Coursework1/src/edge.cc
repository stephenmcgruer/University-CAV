//! \author Stephen McGruer

#include <algorithm>

#include "./edge.h"

namespace computer_animation {

void Edge::AddTriangle(int triangle) {
  triangles_.insert(triangle);
}

bool Edge::operator== (const Edge &edge) const {
  return (this->v1_ == edge.v1_ && this->v2_ == edge.v2_) ||
         (this->v1_ == edge.v2_ && this->v2_ == edge.v1_);
}
}
