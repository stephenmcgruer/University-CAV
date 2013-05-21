//! \author Stephen McGruer

// A set of utility functions.

#ifndef SRC_CAV_UTILS_H_
#define SRC_CAV_UTILS_H_

#include <vector>

#include "./bone.h"
#include "./edge.h"
#include "./matrix-inl.h"
#include "./vector3d-inl.h"

namespace computer_animation {

//! \brief Searches a list of edges for an edge.
//!
//! Returns the index of the first match, or -1 if there are no matches.
int FindEdge(const Edge &edge, const std::vector<Edge> &edge_list);

//! \brief Creates an identity matrix.
void CreateIdentityMatrix(Matrix<float> *f);

//! \brief Creates a matrix to move an object in 3D space.
void CreateTranslationMatrix(Matrix<float> *f,
    const Vector3d<float> &translation);

//! \brief Creates a matrix to rotate an object in the x-axis around
//! the origin.
void CreateXRotMatrix(Matrix<float> *f, float theta);

//! \brief Creates a matrix to rotate an object in the y-axis around
//! the origin.
void CreateYRotMatrix(Matrix<float> *f, float theta);

//! \brief Creates a matrix to rotate an object in the z-axis around
//! the origin.
void CreateZRotMatrix(Matrix<float> *f, float theta);
}
#endif  // SRC_CAV_UTILS_H_
